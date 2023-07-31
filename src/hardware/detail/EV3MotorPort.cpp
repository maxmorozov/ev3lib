/*
 * Ev3MotorPort.cpp
 */

#include <exceptions/EV3HardwareExceptions.h>
#include <utils/type_utils.h>
#include "EV3MotorPort.h"

using namespace std;

namespace ev3lib::hardware::detail {

    EV3MotorPort::EV3MotorPort(EV3DeviceManager* manager, uint8_t port)
            : m_manager(manager), m_port(port) {
        open();
    }

    EV3MotorPort::~EV3MotorPort() {
        close();
        m_manager->disconnect(m_port, PortType::Motor);
    }


    void EV3MotorPort::setPower(int power) {
        uint8_t command[3];
        command[0] = utils::to_underlying(OutputCommand::Power);
        command[1] = m_port;
        command[2] = power;
        m_manager->m_pwmDevice.sendCommand(command);
    }

    void EV3MotorPort::stop(bool flt) {
        uint8_t command[3];
        command[0] = utils::to_underlying(OutputCommand::Stop);
        command[1] = m_port;
        command[2] = flt ? 0 : 1;
        m_manager->m_pwmDevice.sendCommand(command);
    }

    /**
     * returns tachometer count
     */
    int EV3MotorPort::getTachoCount() const {
        return m_manager->m_encoderDevice.getSensorData()[m_port].tachoCnt;
    }

    /**
     * resets the tachometer count to 0;
     */
    void EV3MotorPort::resetTachoCount() {
        uint8_t command[2];
        command[0] = utils::to_underlying(OutputCommand::ClearCount);
        command[1] = m_port;
        m_manager->m_pwmDevice.sendCommand(command);
    }

    /**
     * Starts and stops the motor
     */
    void EV3MotorPort::controlMotor(unsigned int power, port::MotorCommand command) {
        // Convert lejos power and mode to EV3 power and mode
        if (command >= port::MotorCommand::Stop) {
            stop(command == port::MotorCommand::Float);
        } else {
            if (power > MAX_POWER) {
                power = MAX_POWER;
            }
            int control;
            if (command == port::MotorCommand::Backward)
                control = -static_cast<int>(power);
            else
                control = static_cast<int>(power);
            setPower(control);
        }
    }

    bool EV3MotorPort::open() {
        try {
            uint8_t command[2];
            command[0] = utils::to_underlying(OutputCommand::Connect);
            command[1] = m_port;
            m_manager->m_pwmDevice.sendCommand(command);
        } catch (const io_error& e) {
            //Bug in the driver. Always throws the exception
        }
        return true;
    }

    void EV3MotorPort::close() {
        try {
            uint8_t command[2];
            command[0] = utils::to_underlying(OutputCommand::Disconnect);
            command[1] = m_port;
            m_manager->m_pwmDevice.sendCommand(command);
        } catch (const io_error& e) {
            //Bug in the driver. Always throws the exception
        }
    }


} /* namespace ev3lib::hardware::detail */
