/*
 * EV3DeviceManager.cpp
 */

#include <boost/exception/all.hpp>

#include <hardware/detail/lms2012/ev3_constants.h>
#include <exceptions/EV3HardwareExceptions.h>
#include <memory>
#include <utils/type_utils.h>

#include "EV3MotorPort.h"
#include "EV3AnalogPort.h"
#include "EV3UartPort.h"
#include "EV3I2CPort.h"

namespace ev3lib::hardware::detail {

    EV3DeviceManager::EV3DeviceManager() : m_openPorts{nullptr} {
    }

    EV3DeviceManager::~EV3DeviceManager() {
        std::for_each(m_openPorts.begin(), m_openPorts.end(),
                      [](DetachSubscriber* item) { if (item != nullptr) item->detach(); });
    }

    DeviceType EV3DeviceManager::getSensorType(port_type port) const {
        return (DeviceType) m_analogDevice.getSensorData()->InDcm[port];
    }

    ConnectionType EV3DeviceManager::getConnectionType(port_type port) const {
        return (ConnectionType) m_analogDevice.getSensorData()->InConn[port];
    }

    void EV3DeviceManager::setPortMode(port_type port, PortType type, AnalogMode mode) {
        uint8_t command[2];
        int8_t offset = type == PortType::Motor ? EV3SensorConstants::SENSORS : 0;
        command[0] = port + offset;
        command[1] = utils::to_underlying(mode);
        m_dcmDevice.sendCommand(command);
    }

    void EV3DeviceManager::disconnect(port_type port, PortType type) {
        if (type == PortType::Sensor) {
            m_openPorts[port] = nullptr;
        }
        setPortMode(port, type, AnalogMode::Disconnected);
    }

    void EV3DeviceManager::connectSensor(port_type port, DetachSubscriber* sensor) {
        if (port >= m_openPorts.size()) {
            throw boost::enable_error_info(std::range_error("Sensor port index is out of range"))
                    << std_range_min(0)
                    << std_range_max(EV3SensorConstants::SENSORS - 1)
                    << std_range_index(port);
        }

        if (m_openPorts[port] == nullptr) {
            setPortMode(port, PortType::Sensor, AnalogMode::Connected);
            m_openPorts[port] = sensor;
            setPortMode(port, PortType::Sensor, AnalogMode::Float);
        } else {
            throw already_open_error("Port is already opened");
        }
    }

    std::unique_ptr<port::AnalogPort> EV3DeviceManager::getAnalogPort(port_type port) {
        return std::make_unique<EV3AnalogPort>(this, port);
    }

    std::unique_ptr<port::UartPort> EV3DeviceManager::getUartPort(port_type port) {
        return std::make_unique<EV3UartPort>(this, port);
    }

    std::unique_ptr<port::I2CPort> EV3DeviceManager::getI2CPort(port_type port) {
        return std::make_unique<EV3I2CPort>(this, port);
    }

    /**
     * Returns internal motor port structure. The clients should not delete it
     */
    port::TachoMotorPort* EV3DeviceManager::getMotorPort(uint8_t port) {
        if (port < m_motorPorts.size()) {
            if (!m_motorPorts[port]) {
                setPortMode(port, PortType::Motor, AnalogMode::Connected);
                m_motorPorts[port] = std::make_unique<EV3MotorPort>(this, port);
            }
            return m_motorPorts[port].get();
        } else {
            throw boost::enable_error_info(std::range_error("Motor index is out of range"))
                    << std_range_min(0)
                    << std_range_max(EV3SensorConstants::MOTORS - 1)
                    << std_range_index(port);
        }
    }

    /**
     * Checks if the button is down
     */
    bool EV3DeviceManager::checkButton(size_t buttonNo) const {
        if (buttonNo < lms2012::BUTTONS) {
            return m_buttonsDevice.getSensorData()->Pressed[buttonNo] != 0;
        }
        throw boost::enable_error_info(std::range_error("Button index is out of range"))
                << std_range_min(0)
                << std_range_max(lms2012::BUTTONS - 1)
                << std_range_index(buttonNo);
    }

    /**
     * Battery voltage
     */
    short EV3DeviceManager::getBatteryVoltage() const {
        return m_analogDevice.getSensorData()->Cell123456;
    }

    /**
     * Current flowing from the battery
     */
    short EV3DeviceManager::getMotorCurrent() const {
        return m_analogDevice.getSensorData()->MotorCurrent;
    }

    /**
     * Current flowing from the battery
     */
    short EV3DeviceManager::getBatteryCurrent() const {
        return m_analogDevice.getSensorData()->BatteryCurrent;
    }

}
