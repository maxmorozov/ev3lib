/*
 * EV3AnalogPort.cpp
 */

#include "EV3AnalogPort.h"
#include "EV3SensorConstants.h"
#include "hardware/ports/SensorType.h"

namespace ev3lib::hardware::detail {

EV3AnalogPort::EV3AnalogPort(EV3DeviceManager* manager, size_t port)
	: m_manager(manager), m_port(port)
{
}

EV3AnalogPort::~EV3AnalogPort()
{
    if (m_manager)
    	m_manager->disconnect(m_port, PortType::Sensor);
}

/**
 * return the voltage present on pin 6 of the sensor port
 * @return raw ADC voltage reading
 */
int EV3AnalogPort::getPin6() const
{
    if (m_manager)
    	return m_manager->m_analogDevice.getSensorData()->InPin6[m_port];
    else
		return 0;
}

/**
 * return the voltage present on pin 1 of the sensor port
 * @return raw ADC voltage reading
 */
int EV3AnalogPort::getPin1() const
{
    if (m_manager)
	    return m_manager->m_analogDevice.getSensorData()->InPin1[m_port];
	else
		return 0;
}

/**
 * sets the sensor type.
 * @return success status
 */
bool EV3AnalogPort::setType(ports::SensorType type)
{
    bool ret = true;
    switch(type)
    {
    case ports::SensorType::NO_SENSOR:
    case ports::SensorType::SWITCH:
    case ports::SensorType::TEMPERATURE:
    case ports::SensorType::CUSTOM:
    case ports::SensorType::ANGLE:
        setPinMode(AnalogMode::Float);
        break;
    case ports::SensorType::LIGHT_ACTIVE:
    case ports::SensorType::SOUND_DBA:
    case ports::SensorType::REFLECTION:
        setPinMode(AnalogMode::Set|AnalogMode::Pin5);
        break;
    case ports::SensorType::LIGHT_INACTIVE:
    case ports::SensorType::SOUND_DB:
    case ports::SensorType::LOWSPEED:
        setPinMode(AnalogMode::Set);
        break;
    case ports::SensorType::LOWSPEED_9V:
        setPinMode(AnalogMode::Set|AnalogMode::Pin1);
        break;
    case ports::SensorType::COLORFULL:
    case ports::SensorType::COLORRED:
    case ports::SensorType::COLORGREEN:
    case ports::SensorType::COLORBLUE:
    case ports::SensorType::COLORNONE:
        // Sensor type and pin modes are aligned
        setPinMode(AnalogMode(type));
        break;

    default:
        ret = false;
    }
    return ret;
}

bool EV3AnalogPort::setPinMode(AnalogMode mode)
{
    if (m_manager != nullptr) {
		m_manager->setPortMode(m_port, PortType::Sensor, mode);
		return true;
	} else {
		return false;
	}
}

void EV3AnalogPort::detach()
{
	m_manager = nullptr;
}


} /* namespace ev3lib::hardware::detail */
