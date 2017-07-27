
#include <boost/exception/all.hpp>
#include <exceptions/EV3HardwareExceptions.h>

#include <algorithm>
#include <hardware/sensor/MultiModeSensor.h>

namespace ev3lib {
namespace hardware {

MultiModeSensor::MultiModeSensor(std::vector<std::unique_ptr<SensorMode>>&& modes, size_t mode)
	: m_modes(std::move(modes)), m_currentMode(mode)
{

}

MultiModeSensor::MultiModeSensor(MultiModeSensor&& other) noexcept
	: m_modes(std::move(other.m_modes)), m_currentMode(other.m_currentMode)
{

}

/**
 * Return a list of string descriptions for the sensors available modes.
 * @return list of string descriptions
 */
std::vector<std::string> MultiModeSensor::getAvailableModes() const
{
	std::vector<std::string> result;
	std::for_each(m_modes.begin(), m_modes.end(), [&](const std::unique_ptr<SensorMode>& mode) {result.push_back(mode->getName());});
	return result;
}

/**
 * Sets the current mode for fetching samples
 * @param mode the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
 */
void MultiModeSensor::setCurrentMode(size_t mode)
{
    if (!isValid(mode)) {
		throw boost::enable_error_info(std::invalid_argument("Invalid mode")) <<
			std_range_min(0) <<
			std_range_max(m_modes.size() - 1) <<
			std_range_index(mode);
    }
    else {
    	m_currentMode = mode;
    }

}

/**
 * Sets the current mode for fetching samples
 * @param modeName the name of the mode. name corresponds with the item value of the list from getAvailableModes().
 */
void MultiModeSensor::setCurrentMode(const std::string& modeName)
{
	auto it = std::find_if(m_modes.begin(), m_modes.end(), [&](const std::unique_ptr<SensorMode>& mode) {return mode->getName() == modeName;});

	if (it != m_modes.end()) {
		m_currentMode = std::distance(m_modes.begin(), it);
	}
}

/** Gets the index number of the current mode.
 * @return the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
 */
size_t MultiModeSensor::getCurrentMode() const
{
	return m_currentMode;
}

/** Gets the number of supported modes
 * @return the number of supported modes
 */
size_t MultiModeSensor::getModeCount() const
{
	return m_modes.size();
}

/**
 * return a string description of this sensor mode
 * @return The description/name of this mode
 */
std::string MultiModeSensor::getName() const
{
	return m_modes[m_currentMode]->getName();
}

/** Returns the number of elements in a sample.<br>
 * The number of elements does not change during runtime.
 * @return
 * the number of elements in a sample
 */
size_t MultiModeSensor::sampleSize() const
{
	return m_modes[m_currentMode]->sampleSize();
}

/** Fetches a sample from a sensor or filter.
 * @param sample
 * The array to store the sample in.
 * @param offset
 * The elements of the sample are stored in the array starting at the offset position.
 */
void MultiModeSensor::fetchSample(float* sample, size_t offset)
{
	return m_modes[m_currentMode]->fetchSample(sample, offset);
}

bool MultiModeSensor::isValid(size_t mode) const {
	return mode < m_modes.size();
}

}}
