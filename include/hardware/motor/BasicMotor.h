#pragma once

#include "robotics/DCMotor.h"
#include <hardware/detail/MotorManager.h>

namespace ev3lib::hardware::motor {

    /**
     * Abstraction for basic motor operations.
     *
     * @author Lawrie Griffiths.
     */
    class BasicMotor : public robotics::DCMotor {
    private:
        port::BasicMotorPort* m_port;
        unsigned int m_power;
        port::MotorCommand m_currentState;

        /**
         * Sets the motor state according the object's state
         */
        void updateState();

    public:
        explicit BasicMotor(port::BasicMotorPort* port);

        /**
         * Sets power and direction using one command.
         * Positive power values means rotating forward,
         * negative values means rotating backward
         *
         * @param power PWM value from -100 to 100
         */
        void controlMotor(int power);

        /**
         * Sets the output power in percents
         */
        void setPower(unsigned int power) override;

        /**
         * Returns the current motor power setting.
         *
         * @return current power 0-100
         */
        unsigned int getPower() const override;

        /**
         * Rotate the motor in the forward direction
         */
        void forward() override;

        /**
         * Rotate the motor in the backward direction
         */
        void backward() override;

        /**
         * Stops rotation and leaves the circuit closed to brake the motor
         */
        void stop() override;

        /**
         * Stops rotation and leaves the circuit opened. This lets the motor to rotate freely.
         */
        void flt() override;

        /**
         * Returns true iff the motor is in motion.
         *
         * @return true iff the motor is currently in motion.
         */
        bool isMoving() override;
    };

}