/*
 * EV3UartSensor.cpp
 *
 *  Created on: 08 ���. 2014 �.
 *      Author: Max
 */
#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/sensor/UartSensor.h>

namespace ev3lib {
namespace hardware {

UartSensor::UartSensor(std::unique_ptr<detail::UartPort>&& port, std::vector<std::unique_ptr<SensorMode>>&& modes)
	: UartSensor(std::move(port), std::move(modes), 0)
{

}

UartSensor::UartSensor(std::unique_ptr<detail::UartPort>&& port, std::vector<std::unique_ptr<SensorMode>>&& modes, size_t mode)
	: MultiModeSensor(std::move(modes), mode), m_port(std::move(port))
{
    if (!port->setMode(mode))
        throw device_error("Unable to initialize device");
}

UartSensor::UartSensor(UartSensor&& other)
	: MultiModeSensor(std::move(other)), m_port(std::move(other.m_port))
{
}

void UartSensor::switchMode(size_t newMode)
{
    if (m_currentMode != newMode) {
    	if (!m_port->setMode(newMode)) {
    		throw boost::enable_error_info(std::invalid_argument("Invalid mode")) <<
    			std_range_min(0) <<
    			std_range_max(m_modes.size() - 1) <<
    			std_range_index(newMode);
    	}
    }
}


/**
 * Reset the sensor
 */
void UartSensor::reset()
{
	m_port->resetSensor();
}

}}


