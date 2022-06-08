#include <limits>
#include <vector>
#include <boost/endian.hpp>
#include <boost/exception/all.hpp>
#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/sensor/CurrentSensorINA226.h>

namespace ev3lib::hardware::sensor {

    CurrentSensorINA226::CurrentSensorINA226(std::unique_ptr<ports::I2CPort> port, uint8_t address, ports::SensorType type)
            : I2CSensor(std::move(port), address, type) {

        m_modes.push_back(std::make_unique<CombinedMode>(this));
        m_modes.push_back(std::make_unique<PowerMode>(this));
        m_modes.push_back(std::make_unique<ShuntVoltageMode>(this));

        calibrate(0.1f, 1.0f, 1, 0);
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
        boost::endian::big_int16_t buf = m_calibrationValue;

        static_assert(sizeof(int16_t) == sizeof(buf));

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
        boost::endian::big_uint16_t config = uint16_t(avg) << 9 | uint16_t(busConvTime) << 6 | uint16_t(shuntConvTime) << 3 | uint16_t(mode);;

        sendData(REG_CONFIG, gsl::make_span(config.data(), sizeof(config)));
    }

    int16_t CurrentSensorINA226::calculateCalibrationRegister(float maxCurrent) const {
        float maxPossibleI = VSHUNT_MAX / m_shuntValue;
        // Calculate possible range of LSBs (Min = 15-bit)
        // MinimumLSB = MaxExpected_I/32768
        float maxExpectedI = std::min(maxPossibleI, maxCurrent);
        float currentLSB = maxExpectedI / 32768;
        int calibrationRegister = int(CURRENT_SCALING_FACTOR / (currentLSB * m_shuntValue));

        return calibrationRegister > std::numeric_limits<int16_t>::max() ?
               std::numeric_limits<int16_t>::max() :
               int16_t(calibrationRegister);
    }

    /**
     * Calculates the current conversion ratio.
     * Transforms the raw units to mA.
     *
     * @param calibrationValue the calibration register value
     * @return the current conversion ratio.
     */
    float CurrentSensorINA226::calculateCurrentMultiplier(int16_t calibrationValue) const {
        return CURRENT_SCALING_FACTOR / float(calibrationValue) / m_shuntValue * 1000;
    }

    /**
     * Fetches a sample from a sensor or filter.
     *
     * @param sample The buffer to store the sample in.
     */
    void CurrentSensorINA226::fetchSample(gsl::span<float> sample) {
        currentMode()->fetchSample(sample);
    }

    std::string CurrentSensorINA226::getName() const {
        return currentMode()->getName();
    }

    std::vector<std::string> CurrentSensorINA226::getAvailableModes() const {
        std::vector<std::string> result;
        for (auto &mode: m_modes) {
            result.push_back(mode->getName());
        }
        return result;
    }

    void CurrentSensorINA226::setCurrentMode(size_t mode) {
        if (isValidMode(mode)) {
            m_currentMode = mode;
        } else {
            throw boost::enable_error_info(std::invalid_argument("Invalid sensor mode"))
                    << std_range_min(0)
                    << std_range_max(m_modes.size() - 1)
                    << std_range_index(mode);
        }
    }

    void CurrentSensorINA226::setCurrentMode(const std::string &modeName) {
        auto it = std::find_if(m_modes.begin(), m_modes.end(), [&](const auto &mode) { return mode->getName() == modeName; });

        if (it != m_modes.end()) {
            m_currentMode = static_cast<size_t>(std::distance(m_modes.begin(), it));
        }
    }

    size_t CurrentSensorINA226::sampleSize() const {
        return currentMode()->sampleSize();
    }

    bool CurrentSensorINA226::isValidMode(size_t mode) const {
        return mode >= 0 && mode < m_modes.size();
    }

    //Modes
    void CurrentSensorINA226::CombinedMode::fetchSample(gsl::span<float> sample) {
        // Sometimes a sharp load will reset the INA226, which will
        // reset the cal register, meaning CURRENT and POWER will
        // not be available ... avoid this by always setting a cal
        // value even if it's an unfortunate extra step
        //boost::endian::big_int16_t calibrationReg = m_sensor->m_calibrationValue;
        //m_sensor->sendData(REG_CALIBRATION, gsl::make_span(calibrationReg.data(), sizeof(calibrationReg)));

        boost::endian::big_int16_t currentRaw;
        m_sensor->getData(REG_CURRENT, gsl::make_span(currentRaw.data(), sizeof(currentRaw)));

        boost::endian::big_int16_t voltageRaw;
        m_sensor->getData(REG_BUS_VOLTAGE, gsl::make_span(voltageRaw.data(), sizeof(voltageRaw)));

        //std::cout<<currentRaw<<", "<<voltageRaw<<", "<<m_sensor->m_calibrationValue<<", "<<m_sensor->m_currentMultiplier_mA<<std::endl;

        sample[0] = currentRaw * m_sensor->m_currentMultiplier_mA + m_sensor->m_currentOffset_mA;
        sample[1] = voltageRaw * VOLTAGE_LSB;
    }

    void CurrentSensorINA226::PowerMode::fetchSample(gsl::span<float> sample) {
        // Sometimes a sharp load will reset the INA226, which will
        // reset the cal register, meaning CURRENT and POWER will
        // not be available ... avoid this by always setting a cal
        // value even if it's an unfortunate extra step
        //boost::endian::big_int16_t calibrationReg = m_sensor->m_calibrationValue;
        //m_sensor->sendData(REG_CALIBRATION, gsl::make_span(calibrationReg.data(), sizeof(calibrationReg)));

        boost::endian::big_int16_t powerRaw;
        m_sensor->getData(REG_POWER, gsl::make_span(powerRaw.data(), sizeof(powerRaw)));

        sample[0] = powerRaw * m_sensor->m_powerMultiplier_mW;
    }

    void CurrentSensorINA226::ShuntVoltageMode::fetchSample(gsl::span<float> sample) {
        boost::endian::big_int16_t vShuntRaw;
        m_sensor->getData(REG_SHUNT_VOLTAGE, gsl::make_span(vShuntRaw.data(), sizeof(vShuntRaw)));

        sample[0] = vShuntRaw * VSHUNT_LSB;
    }
}