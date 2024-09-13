/*
 * EV3DeviceManager.h
 */

#pragma once

#include <memory>
#include <hardware/detail/device_traits.h>
#include <hardware/detail/ev3_device.h>
#include <hardware/detail/SensorsManager.h>
#include <hardware/detail/MotorManager.h>
#include <hardware/detail/UIManager.h>
#include <hardware/detail/BatteryManager.h>
#include "EV3SensorConstants.h"
#include "DetachSubscriber.h"

namespace ev3lib::hardware::detail {

    struct DeviceInfo {
        ConnectionType connectionType = ConnectionType::None;
    };

    class EV3DeviceManager : public SensorsManager, public MotorManager, public UIManager, public BatteryManager, utils::noncopyable {
        friend class EV3MotorPort;

        friend class EV3AnalogPort;

        friend class EV3UartPort;

        friend class EV3I2CPort;

    private:
        EV3Device<device_type::dcm> m_dcmDevice;

        EV3InputDevice<device_type::analog_sensor> m_analogDevice;
        EV3InputDevice<device_type::uart_sensor> m_uartDevice;
        EV3Device<device_type::i2c_sensor> m_i2cDevice;

        EV3InputDevice<device_type::motor_encoder> m_encoderDevice;
        EV3Device<device_type::pwm_motor> m_pwmDevice;

        EV3InputDevice<device_type::ui> m_buttonsDevice;

        std::array<std::unique_ptr<port::TachoMotorPort>, EV3SensorConstants::MOTORS> m_motorPorts;

        std::array<DetachSubscriber*, EV3SensorConstants::SENSORS> m_openPorts;

        void connectSensor(port_type port, DetachSubscriber* sensor);

    public:
        EV3DeviceManager();

        ~EV3DeviceManager() override;

        DeviceType getSensorType(port_type port) const override;

        ConnectionType getConnectionType(port_type port) const override;

        void setPortMode(port_type port, PortType type, AnalogMode mode) override;

        void disconnect(port_type port, PortType type) override;

        std::unique_ptr<port::AnalogPort> getAnalogPort(port_type port) override;

        std::unique_ptr<port::UartPort> getUartPort(port_type port) override;

        std::unique_ptr<port::I2CPort> getI2CPort(port_type port) override;

        /**
         * Returns internal motor port structure. The clients should not delete it
         */
        port::TachoMotorPort* getMotorPort(uint8_t port) override;

        /**
         * Checks if the button is down
         */
        bool checkButton(size_t buttonNo) const override;

        /**
         * Battery voltage
         */
        short getBatteryVoltage() const override;

        /**
         * Current flowing from the battery
         */
        short getMotorCurrent() const override;

        /**
         * Current flowing from the battery
         */
        short getBatteryCurrent() const override;

    };

}
