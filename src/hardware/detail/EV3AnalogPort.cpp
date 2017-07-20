/*
 * EV3AnalogPort.cpp
 */

#include "EV3AnalogPort.h"
#include "EV3SensorConstants.h"
#include "EV3SensorType.h"

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
bool EV3AnalogPort::setType(int type)
{
    bool ret = true;
    switch(EV3SensorType(type))
    {
    case EV3SensorType::NO_SENSOR:
    case EV3SensorType::SWITCH:
    case EV3SensorType::TEMPERATURE:
    case EV3SensorType::CUSTOM:
    case EV3SensorType::ANGLE:
        setPinMode(AnalogMode::Float);
        break;
    case EV3SensorType::LIGHT_ACTIVE:
    case EV3SensorType::SOUND_DBA:
    case EV3SensorType::REFLECTION:
        setPinMode(AnalogMode::Set|AnalogMode::Pin5);
        break;
    case EV3SensorType::LIGHT_INACTIVE:
    case EV3SensorType::SOUND_DB:
        setPinMode(AnalogMode::Set);
        break;
    case EV3SensorType::LOWSPEED:
        setPinMode(AnalogMode::Set);
        break;
    case EV3SensorType::LOWSPEED_9V:
        setPinMode(AnalogMode::Set|AnalogMode::Pin1);
        break;
    case EV3SensorType::COLORFULL:
    case EV3SensorType::COLORRED:
    case EV3SensorType::COLORGREEN:
    case EV3SensorType::COLORBLUE:
    case EV3SensorType::COLORNONE:
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
    if (m_manager) {
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


} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
