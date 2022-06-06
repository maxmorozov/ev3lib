#include <limits>
#include <boost/endian.hpp>
#include <hardware/sensor/CurrentSensorINA226.h>

namespace ev3lib::hardware::sensor {

    CurrentSensorINA226::CurrentSensorINA226(std::unique_ptr<ports::I2CPort> port)
            : I2CSensor(std::move(port)) {

    }

    CurrentSensorINA226::CurrentSensorINA226(std::unique_ptr<ports::I2CPort> port, uint8_t address)
            : I2CSensor(std::move(port), address) {

    }

    CurrentSensorINA226::CurrentSensorINA226(std::unique_ptr<ports::I2CPort> port, uint8_t address, ports::SensorType type)
            : I2CSensor(std::move(port), address, type) {

    }

    /**
     * Initializes the sensor with the maximum expected current value in A
     *
     * @param shuntValue shunt value in Ohm
     * @param maxCurrent max expected current in A
     * @param ratio the current correction coefficient
     * @param offset the zero current offset in mA
     */
    void CurrentSensorINA226::calibrate(float shuntValue, float maxCurrent, float ratio, float offset) {
        m_shuntValue = shuntValue;
        m_currentOffset_mA = offset;

        m_calibrationValue = calculateCalibrationRegister(maxCurrent);
        m_currentMultiplier_mA = calculateCurrentMultiplier(m_calibrationValue) * ratio;
        m_powerMultiplier_mW = 25.f * m_currentMultiplier_mA;

        // Set Calibration register to 'Cal' calculated above
        boost::endian::big_uint16_t buf = m_calibrationValue;

        static_assert(sizeof(uint16_t) == sizeof(buf));

        sendData(REG_CALIBRATION, gsl::make_span(buf.data(), sizeof(buf)));

        // Set Config register to take into account the settings above
        //Reading of two registers takes 13 ms, so we can use 4 samples for smoothing (8.8 ms)
        configure(Average::AVERAGES_4, BusConversionTime::TIME_1100US, ShuntConversionTime::TIME_1100US, Mode::SHUNT_BUS_CONT);
    }

    /**
     * Setup reading mode.
     * Measure time is (bus time + shunt time) * average count.
     *
     * @param avg number of samples to calculate average
     * @param busConvTime bus voltage conversion time constant
     * @param shuntConvTime shunt volatge conversion time constante
     * @param mode operating mode constant
     */
    void CurrentSensorINA226::configure(CurrentSensorINA226::Average avg, CurrentSensorINA226::BusConversionTime busConvTime,
                                        CurrentSensorINA226::ShuntConversionTime shuntConvTime, CurrentSensorINA226::Mode mode) {
        boost::endian::big_uint16_t config = uint16_t(avg) << 9 | uint16_t(busConvTime) << 6 | uint16_t(shuntConvTime) << 3 | uint16_t(mode);

        sendData(REG_CONFIG, gsl::make_span(config.data(), sizeof(config)));
    }

    int CurrentSensorINA226::calculateCalibrationRegister(float maxCurrent) const {
        float maxPossibleI = VSHUNT_MAX / m_shuntValue;
        // Calculate possible range of LSBs (Min = 15-bit)
        // MinimumLSB = MaxExpected_I/32768
        float maxExpectedI = std::min(maxPossibleI, maxCurrent);
        float currentLSB = maxExpectedI / 32768;
        int calibrationRegister = (int)(CURRENT_SCALING_FACTOR / (currentLSB * m_shuntValue));

        return calibrationRegister > std::numeric_limits<int16_t>::max() ? std::numeric_limits<int16_t>::max() : calibrationRegister;
    }

    /**
     * Calculates the current conversion ratio.
     * Transforms the raw units to mA.
     *
     * @param calibrationValue the calibration register value
     * @return the current conversion ratio.
     */
    float CurrentSensorINA226::calculateCurrentMultiplier(int calibrationValue) const {
        return CURRENT_SCALING_FACTOR / calibrationValue / m_shuntValue * 1000;
    }

}