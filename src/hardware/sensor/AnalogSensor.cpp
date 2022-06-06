/*
 * AnalogSensor.cpp
 */

#include <stdexcept>
#include <hardware/sensor/AnalogSensor.h>

namespace ev3lib::hardware::sensor {

AnalogSensor::AnalogSensor(std::unique_ptr<ports::AnalogPort> port)
	: m_port(std::move(port))
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
void AnalogSensor::switchType(ports::SensorType newType)
{
    if (m_currentType != newType)
    {
        if (!m_port->setType(newType))
            throw std::logic_error("Invalid sensor mode");
        m_currentType = newType;
    }
}

} /* namespace ev3lib::hardware */
