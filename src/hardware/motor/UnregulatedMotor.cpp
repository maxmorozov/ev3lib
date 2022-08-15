/*
 * motor.cpp
 */
#include <hardware/motor/UnregulatedMotor.h>

namespace ev3lib::hardware::motor {

    using namespace detail;

    UnregulatedMotor::UnregulatedMotor(port::TachoMotorPort* port)
            : m_basicMotor(port), m_tachoPort(port) {

    }

    /**
     * Sets the output power in percents
     */
    void UnregulatedMotor::setPower(unsigned int power) {
        m_basicMotor.setPower(power);
    }

    /**
     * Returns the current motor power setting.
     *
     * @return current power 0-100
     */
    unsigned int UnregulatedMotor::getPower() const {
        return m_basicMotor.getPower();
    }

    /**
     * Rotate the motor in the forward direction
     */
    void UnregulatedMotor::forward() {
        m_basicMotor.forward();
    }

    /**
     * Rotate the motor in the backward direction
     */
    void UnregulatedMotor::backward() {
        m_basicMotor.backward();
    }

    /**
     * Stops rotation and leaves the circuit closed to brake the motor
     */
    void UnregulatedMotor::stop() {
        m_basicMotor.stop();
    }

    /**
     * Stops rotation and leaves the circuit opened. This lets the motor to rotate freely.
     */
    void UnregulatedMotor::flt() {
        m_basicMotor.flt();
    }

    /**
     * Returns true iff the motor is in motion.
     *
     * @return true iff the motor is currently in motion.
     */
    bool UnregulatedMotor::isMoving() {
        return m_basicMotor.isMoving();
    }

    /**
     * returns tachometer count
     */
    int UnregulatedMotor::getTachoCount() const {
        return m_tachoPort->getTachoCount();
    }

    /**
     * resets the tachometer count to 0;
     */
    void UnregulatedMotor::resetTachoCount() {
        m_tachoPort->resetTachoCount();
    }

}


