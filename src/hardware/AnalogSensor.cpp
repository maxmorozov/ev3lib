/*
 * AnalogSensor.cpp
 *
 *  Created on: 23 марта 2015 г.
 *      Author: Max
 */

#include <hardware/AnalogSensor.h>

namespace ev3lib {
namespace hardware {

AnalogSensor::AnalogSensor(std::unique_ptr<detail::AnalogPort>&& port)
	: m_port(std::move(port))
{

}

AnalogSensor::AnalogSensor(AnalogSensor&& other)
	: m_port(std::move(other.m_port))
{

}

AnalogSensor::~AnalogSensor()
{
}


int AnalogSensor::getData() const
{
	return m_port->getPin1();
}

} /* namespace hardware */
} /* namespace ev3lib */
