#include <chrono>
#include <thread>
#include <hardware/sensor/ImuLsm6ds3.h>
#include <exceptions/EV3HardwareExceptions.h>

namespace ev3lib {
namespace hardware {

const float ImuLsm6ds3::gyroScale[5] = {8.75e-3f, 17.5e-3f, 35e-3f, 70e-3f, 4.375e-3f};//in degree per second / digit
const float ImuLsm6ds3::accelScale[4] = {2.0f / ACCEL_SCALE, 4.0f / ACCEL_SCALE, 8.0f / ACCEL_SCALE , 16.0f / ACCEL_SCALE}; //in g / digit
const constexpr ImuLsm6ds3::Mode ImuLsm6ds3::modes[3];

ImuLsm6ds3::ImuLsm6ds3(std::unique_ptr<detail::UartPort>&& port, bool rawMode)
	: UartSensor(std::move(port), std::move(createModes())), m_rawMode(rawMode)
{

}

//Recreate modes because they have pointer to the sensor object
ImuLsm6ds3::ImuLsm6ds3(ImuLsm6ds3&& other) noexcept
	: UartSensor(std::move(other)),
	  m_accelScale(other.m_accelScale), m_gyroScale(other.m_gyroScale), m_rawMode(other.m_rawMode)
{


}


std::vector<MultiModeSensor::ModeInfo> ImuLsm6ds3::createModes()
{
	std::vector<ModeInfo> result;
    for(Mode mode: modes) {
        result.push_back(ModeInfo{mode.name.value(), mode.sampleSize});
    }
	return result;
}

void ImuLsm6ds3::reset()
{
    uint8_t buffer = DEVICE_RESET;
    m_port->write(&buffer, 0, 1);
}

/** Fetches a sample from a sensor or filter.
 *
 * @param sample The array to store the sample in.
 * @param offset The elements of the sample are stored in the array starting at the offset position.
*/
void ImuLsm6ds3::fetchSample(float* sample, size_t offset)
{
    short buffer[maxSampleSize()];

    readSample(getModeId(m_currentMode), buffer, sampleSize());

    //Use switch instead of calling the mode's object method to simplify move constructor and move operator
    switch(m_currentMode) {
        case 0:
            scaleCombined(buffer, sample, offset);
            break;
        case 1:
            scaleAccel(buffer, sample, offset);
            break;
        case 2:
            scaleGyro(buffer, sample, offset);
            break;

        default:
            throw boost::enable_error_info(std::invalid_argument("Invalid mode")) <<
                  std_range_min(0) <<
                  std_range_max(m_modes.size() - 1) <<
                  std_range_index(m_currentMode);
    }
}


//Apply the current scale to the sample
void ImuLsm6ds3::scaleCombined(const int16_t* buffer, float* sample, size_t offset)
{
    float accelScale = getAccelScale();
    float gyroScale = getGyroScale();
    //Accelerometer
    for (size_t i = 0; i < 3; ++i) {
        sample[offset + i] = buffer[i] * accelScale;
    }
    for (size_t i = 3; i < sampleSize(); ++i) {
        sample[offset + i] = buffer[i] * gyroScale;
    }
}

void ImuLsm6ds3::scaleAccel(const int16_t* buffer, float* sample, size_t offset)
{
    float accelScale = getAccelScale();
    for (size_t i = 0; i < sampleSize(); ++i) {
        sample[offset + i] = buffer[i] * accelScale;
    }
}

void ImuLsm6ds3::scaleGyro(const int16_t* buffer, float* sample, size_t offset)
{
    float gyroScale = getGyroScale();
    for (size_t i = 0; i < sampleSize(); ++i) {
        sample[offset + i] = buffer[i] * gyroScale;
    }
}


//Change scale support

/**
 * Changes the accelerometer full-scale range
 *
 * @param scaleNo scale range index
 * @return true if the current scale range has been successfully changed
 */
bool ImuLsm6ds3::setAccelerometerScale(size_t scaleNo)
{
    if (scaleNo < count_of(accelScale)) {
    	m_accelScale = scaleNo;
        return setScale(ACC_SCALE_2G + scaleNo);
    }
    return false;
}

/**
 * Changes the gyroscope full-scale range
 *
 * @param scaleNo scale range index
 * @return true if the current scale range has been successfully changed
 */
bool ImuLsm6ds3::setGyroscopeScale(size_t scaleNo)
{
    if (scaleNo < count_of(gyroScale)) {
    	m_gyroScale = scaleNo;
        return setScale(GYRO_SCALE_245DPS + scaleNo);
    }
    return false;
}

//EEPROM

/**
 * Update accelerometer EEPROM
 *
 * @param scaleNo scale index
 * @param data EEPROM data (4x3 matrix of 16-bit integers)
 * @param size size of EEPROM data in words
 * @return true if the EEPROM data has been successfully written
 */
bool ImuLsm6ds3::writeAccelerometerEeprom(size_t scaleNo, const int16_t* data, size_t size)
{
    return writeEeprom(CALIBRATE_ACC_2G + scaleNo, data, size);
}

/**
 * Update gyroscope EEPROM
 *
 * @param scaleNo scale index
 * @param data EEPROM data (4x3 matrix of 16-bit integers)
 * @param size size of EEPROM data in words
 * @return true if the EEPROM data has been successfully written
 */
bool ImuLsm6ds3::writeGyroscopeEeprom(size_t scaleNo, const int16_t* data, size_t size)
{
    return writeEeprom(CALIBRATE_GYRO_245DPS + scaleNo, data, size);
}


bool ImuLsm6ds3::writeEeprom(int writeCommand, const int16_t* data, size_t size)
{
    std::vector<uint8_t> command(size * sizeof(int16_t) + 1);
    command[0] = (uint8_t) writeCommand;
    std::copy(data, data + size, (int16_t*)&command[1]);

    bool success = (size_t)m_port->write(&command.front(), 0, command.size()) == command.size();
    if (success) {
        //Wait for writing the data to EEPROM
    	std::this_thread::sleep_for(std::chrono::milliseconds(command.size() * 3));
    }
    return success;
}

bool ImuLsm6ds3::setScale(int scaleCommand)
{
	auto command = (uint8_t)scaleCommand;
    bool success = m_port->write(&command, 0, sizeof(command)) == sizeof(command);
    if (success) {
    	std::this_thread::sleep_for(std::chrono::milliseconds(SCALE_SWITCH_DELAY));
    }
    return success;

}

void ImuLsm6ds3::readSample(size_t mode, int16_t* buffer, size_t sampleSize) {
	if (mode != getCurrentMode()) {
		switchMode(mode);
		setAccelerometerScale(0);
		setGyroscopeScale(0);
	}
	m_port->read((uint8_t*)buffer, 0, sampleSize * sizeof(int16_t));
}

float ImuLsm6ds3::getAccelScale() const
{
	if (m_rawMode)
		return 1;
	else
		return accelScale[m_accelScale];
}

float ImuLsm6ds3::getGyroScale() const
{
	if (m_rawMode)
		return 1;
	else
		return gyroScale[m_gyroScale];
}

}}
