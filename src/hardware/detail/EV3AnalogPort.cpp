/*
 * EV3AnalogPort.cpp
 *
 *  Created on: 23 февр. 2015 г.
 *      Author: Max
 */

#include "EV3AnalogPort.h"
#include "EV3SensorConstants.h"

namespace ev3lib {
namespace hardware {
namespace detail {

namespace {
	typedef BufferCommand<unsigned char, 3> Command3;
	typedef BufferCommand<unsigned char, 2> Command2;
}


EV3AnalogPort::EV3AnalogPort(EV3DeviceManager* manager, size_t port)
	: m_manager(manager), m_port(port)
{
	m_manager->setPortMode(m_port, PortType::Sensor, AnalogMode::Connected);
	m_manager->setPortMode(m_port, PortType::Sensor, AnalogMode::Float);
}

EV3AnalogPort::~EV3AnalogPort()
{
	m_manager->setPortMode(m_port, PortType::Sensor, AnalogMode::Disconnected);
}

/**
 * return the voltage present on pin 6 of the sensor port
 * @return voltage reading
 */
float EV3AnalogPort::getPin6() const
{
    return m_manager->m_analogDevice.getSensorData()->InPin6[m_port] * EV3SensorConstants::ADC_REF / EV3SensorConstants::ADC_RES;
}

/**
 * return the voltage present on pin 1 of the sensor port
 * @return voltage reading
 */
float EV3AnalogPort::getPin1() const
{
    return m_manager->m_analogDevice.getSensorData()->InPin1[m_port] * EV3SensorConstants::ADC_REF / EV3SensorConstants::ADC_RES;
}


} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
