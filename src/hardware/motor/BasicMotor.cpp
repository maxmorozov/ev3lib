//
// Created by max on 15.08.2022.
//

#include <hardware/motor/BasicMotor.h>

namespace ev3lib::hardware::motor {

    BasicMotor::BasicMotor(port::BasicMotorPort* port)
            : m_port(port), m_power(0), m_currentState(port::MotorCommand::Float) {

    }

    /**
     * Sets the motor state according the object's state
     */
    void BasicMotor::updateState() {
        m_port->controlMotor(m_power, m_currentState);
    }

    /**
     * Sets the output power in percents
     */
    void BasicMotor::setPower(unsigned int power) {
        m_power = power;
        updateState();
    }

    /**
     * Returns the current motor power setting.
     *
     * @return current power 0-100
     */
    unsigned int BasicMotor::getPower() const {
        return m_power;
    }

    /**
     * Rotate the motor in the forward direction
     */
    void BasicMotor::forward() {
        m_currentState = port::MotorCommand::Forward;
        updateState();
    }

    /**
     * Rotate the motor in the backward direction
     */
    void BasicMotor::backward() {
        m_currentState = port::MotorCommand::Backward;
        updateState();
    }

    /**
     * Stops rotation and leaves the circuit closed to brake the motor
     */
    void BasicMotor::stop() {
        m_currentState = port::MotorCommand::Stop;
        updateState();
    }

    /**
     * Stops rotation and leaves the circuit opened. This lets the motor to rotate freely.
     */
    void BasicMotor::flt() {
        m_currentState = port::MotorCommand::Float;
        updateState();
    }

    /**
     * Returns true iff the motor is in motion.
     *
     * @return true iff the motor is currently in motion.
     */
    bool BasicMotor::isMoving() {
        return (m_currentState == port::MotorCommand::Forward || m_currentState == port::MotorCommand::Backward);
    }

    void BasicMotor::controlMotor(int power) {
        if (power > 0) {
            m_power = power;
            m_currentState = port::MotorCommand::Forward;
        }
        else if (power < 0) {
            m_power = -power;
            m_currentState = port::MotorCommand::Backward;
        }
        else {
            m_power = 0;
            m_currentState = port::MotorCommand::Stop;
        }

        updateState();
    }

}