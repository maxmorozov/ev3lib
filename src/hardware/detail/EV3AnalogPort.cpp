/*
 * EV3AnalogPort.cpp
 */

#include "EV3AnalogPort.h"
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::detail {

    EV3AnalogPort::EV3AnalogPort(EV3DeviceManager* manager, size_t port)
            : m_manager(manager), m_port(port) {
        //Try to connect the sensor in the constructor to avoid
        //destructor calling if another sensor is already attached to this port
        manager->connectSensor(port, this);
    }

    EV3AnalogPort::~EV3AnalogPort() {
        close();
    }

    /**
     * return the voltage present on pin 6 of the sensor port
     * @return raw ADC voltage reading
     */
    short EV3AnalogPort::getPin6() const {
        if (m_manager)
            return m_manager->m_analogDevice.getSensorData()->InPin6[m_port];
        else
            return 0;
    }

    /**
     * return the voltage present on pin 1 of the sensor port
     * @return raw ADC voltage reading
     */
    short EV3AnalogPort::getPin1() const {
        if (m_manager)
            return m_manager->m_analogDevice.getSensorData()->InPin1[m_port];
        return 0;
    }

    /**
     * sets the sensor type.
     * @return success status
     */
    bool EV3AnalogPort::setType(port::SensorType type) {
        bool ret = true;
        switch (type) {
            case port::SensorType::NO_SENSOR:
            case port::SensorType::SWITCH:
            case port::SensorType::TEMPERATURE:
            case port::SensorType::CUSTOM:
            case port::SensorType::ANGLE:
                setPinMode(AnalogMode::Float);
                break;
            case port::SensorType::LIGHT_ACTIVE:
            case port::SensorType::SOUND_DBA:
            case port::SensorType::REFLECTION:
                setPinMode(AnalogMode::Set | AnalogMode::Pin5);
                break;
            case port::SensorType::LIGHT_INACTIVE:
            case port::SensorType::SOUND_DB:
            case port::SensorType::LOWSPEED:
                setPinMode(AnalogMode::Set);
                break;
            case port::SensorType::LOWSPEED_9V:
                setPinMode(AnalogMode::Set | AnalogMode::Pin1);
                break;
            case port::SensorType::COLORFULL:
            case port::SensorType::COLORRED:
            case port::SensorType::COLORGREEN:
            case port::SensorType::COLORBLUE:
            case port::SensorType::COLORNONE:
                // Sensor type and pin modes are aligned
                setPinMode(AnalogMode(type));
                break;

            default:
                ret = false;
        }
        return ret;
    }

    bool EV3AnalogPort::setPinMode(AnalogMode mode) {
        if (m_manager != nullptr) {
            m_manager->setPortMode(m_port, PortType::Sensor, mode);
            return true;
        }
        return false;
    }

    void EV3AnalogPort::detach() {
        close();
        m_manager = nullptr;
    }

    void EV3AnalogPort::close() {
        if (m_manager) {
            m_manager->disconnect(m_port, PortType::Sensor);
        }
    }

} /* namespace ev3lib::hardware::detail */
