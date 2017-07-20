/*
 * AnalogSensor.cpp
 */

#include <stdexcept>
#include <hardware/sensor/AnalogSensor.h>

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

/**
 * Switch to the selected type (if not already in that type) and delay for the
 * specified period to allow the sensor to settle in the new state. <br>
 * NOTE: This method is intended for use with NXT sensor drivers that use a
 * sensor type to specify the operating mode.
 * @param newType The type to switch to.
 * @param switchDelay Time in mS to delay after the switch.
 */
void AnalogSensor::switchType(int newType)
{
    if (currentType != newType)
    {
        if (!m_port->setType(newType))
            throw std::logic_error("Invalid sensor mode");
        currentType = newType;
    }
}

} /* namespace hardware */
} /* namespace ev3lib */
