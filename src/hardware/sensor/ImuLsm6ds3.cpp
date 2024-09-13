#include <chrono>
#include <thread>
#include <utility>
#include <hardware/sensor/ImuLsm6ds3.h>
#include <exceptions/EV3HardwareExceptions.h>

namespace ev3lib::hardware::sensor {

    const float ImuLsm6ds3::gyroScale[5] = {8.75e-3f, 17.5e-3f, 35e-3f, 70e-3f, 4.375e-3f};//in degree per second / digit
    const float ImuLsm6ds3::accelScale[4] = {2.0f / ACCEL_SCALE, 4.0f / ACCEL_SCALE, 8.0f / ACCEL_SCALE, 16.0f / ACCEL_SCALE}; //in g / digit

    ImuLsm6ds3::ImuLsm6ds3(std::unique_ptr<port::UartPort> port, bool rawMode)
            : UartSensor(std::move(port), createModes()), m_rawMode(rawMode) {

    }

    std::vector<MultiModeSensor::ModeInfo> ImuLsm6ds3::createModes() {
        std::vector<ModeInfo> result;
        for (Mode mode: modes) {
            result.emplace_back(mode.name.value(), mode.sampleSize);
        }
        return result;
    }

    void ImuLsm6ds3::reset() {
        uint8_t buffer = DEVICE_RESET;
        m_port->write(std::span(&buffer, 1));
    }

    /** Fetches a sample from a sensor or filter.
     *
     * @param sample The array to store the sample in.
    */
    void ImuLsm6ds3::fetchSample(std::span<float> sample) {
        short buffer[maxSampleSize()];

        readSample(std::span(buffer, sampleSize()));

        scaleData(std::span(const_cast<const short*>(buffer), sampleSize()), std::span(sample.data(), sampleSize()));
    }

    void ImuLsm6ds3::scaleData(std::span<const int16_t> buffer, std::span<float> sample) {
        //Use switch instead of calling the mode's object method to simplify move constructor and move operator
        switch (m_currentMode) {
            case 0:
                scaleCombined(buffer, sample);
                break;
            case 1:
                scale(buffer, sample, getAccelScale());
                break;
            case 2:
                scale(buffer, sample, getGyroScale());
                break;

            default:
                throw boost::enable_error_info(std::invalid_argument("Invalid mode"))
                        << std_range_min(0)
                        << std_range_max(m_modes.size() - 1)
                        << std_range_index(m_currentMode);
        }
    }

    //Apply the current scale to the sample
    void ImuLsm6ds3::scaleCombined(std::span<const int16_t> source, std::span<float> target) {
        scale(std::span(source.data(), 3), target, getAccelScale());
        scale(std::span(source.data() + 3, 3), std::span(target.data() + 3, 3), getGyroScale());
    }

    void ImuLsm6ds3::scale(std::span<const int16_t> source, std::span<float> target, float scale) {
        auto out = target.begin();
        for (int16_t value: source) {
            *out++ = value * scale;
        }
    }

    //Change scale support

    /**
     * Changes the accelerometer full-scale range
     *
     * @param scaleNo scale range index
     * @return true if the current scale range has been successfully changed
     */
    bool ImuLsm6ds3::setAccelerometerScale(size_t scaleNo) {
        if (scaleNo < utils::count_of(accelScale)) {
            m_accelScale = scaleNo;
            return updateScale(ACC_SCALE_2G + scaleNo);
        }
        return false;
    }

    /**
     * Returns number of supported scales
     *
     * @return number of scales supported by the sensor
     */
    size_t ImuLsm6ds3::getAccelerometerScales() const {
        return utils::count_of(accelScale);
    }

    /**
     * Changes the gyroscope full-scale range
     *
     * @param scaleNo scale range index
     * @return true if the current scale range has been successfully changed
     */
    bool ImuLsm6ds3::setGyroscopeScale(size_t scaleNo) {
        if (scaleNo < utils::count_of(gyroScale)) {
            m_gyroScale = scaleNo;
            return updateScale(GYRO_SCALE_245DPS + scaleNo);
        }
        return false;
    }

    /**
     * Returns number of supported scales
     *
     * @return number of scales supported by the sensor
     */
    size_t ImuLsm6ds3::getGyroscopeScales() const {
        return utils::count_of(gyroScale);
    }

    //EEPROM

    /**
     * Update accelerometer EEPROM
     *
     * @param scaleNo scale index
     * @param data EEPROM data (4x3 matrix of 16-bit integers)
     * @return true if the EEPROM data has been successfully written
     */
    bool ImuLsm6ds3::writeAccelerometerEeprom(size_t scaleNo, std::span<const int16_t> data) {
        return writeEeprom(CALIBRATE_ACC_2G + scaleNo, data);
    }

    /**
     * Update gyroscope EEPROM
     *
     * @param scaleNo scale index
     * @param data EEPROM data (4x3 matrix of 16-bit integers)
     * @return true if the EEPROM data has been successfully written
     */
    bool ImuLsm6ds3::writeGyroscopeEeprom(size_t scaleNo, std::span<const int16_t> data) {
        return writeEeprom(CALIBRATE_GYRO_245DPS + scaleNo, data);
    }


    bool ImuLsm6ds3::writeEeprom(uint8_t writeCommand, std::span<const int16_t> data) {
        std::vector<uint8_t> command(data.size_bytes() + 1);
        command[0] = writeCommand;
        std::copy(data.begin(), data.end(), (int16_t*) &command[1]);

        bool success = m_port->write(command) == command.size();
        if (success) {
            //Wait for writing the data to EEPROM
            std::this_thread::sleep_for(std::chrono::milliseconds(command.size() * 3));
        }
        return success;
    }

    bool ImuLsm6ds3::updateScale(uint8_t scaleCommand) {
        uint8_t command[1] = {scaleCommand};
        bool success = m_port->write(command) == sizeof(command);
        if (success) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SCALE_SWITCH_DELAY));
        }
        return success;

    }

    void ImuLsm6ds3::readSample(std::span<int16_t> buffer) {
        m_port->read(std::span((uint8_t*) (buffer.data()), buffer.size_bytes()));
    }

    float ImuLsm6ds3::getAccelScale() const {
        if (m_rawMode)
            return 1;
        else
            return accelScale[m_accelScale];
    }

    float ImuLsm6ds3::getGyroScale() const {
        if (m_rawMode)
            return 1;
        else
            return gyroScale[m_gyroScale];
    }

    void ImuLsm6ds3::switchMode(size_t newMode) {
        if (newMode != getCurrentMode()) {
            UartSensor::switchMode(newMode);
            setAccelerometerScale(0);
            setGyroscopeScale(0);
        }
    }

}
