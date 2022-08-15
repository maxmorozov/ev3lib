#pragma once

#include <hardware/detail/MotorManager.h>
#include <robotics/EncoderMotor.h>
#include <hardware/motor/BasicMotor.h>

namespace ev3lib::hardware::motor {

    /**
     * Abstraction for an NXT and EV3 motor with no speed regulation.
     */
    class UnregulatedMotor : public robotics::EncoderMotor {
    private:
        BasicMotor m_basicMotor;
        port::TachoMotorPort* m_tachoPort;

    public:
        explicit UnregulatedMotor(port::TachoMotorPort* port);

        /**
         * Sets power and direction using one command.
         * Positive power values means rotating forward,
         * negative values means rotating backward
         *
         * @param power PWM value from -100 to 100
         */
        void controlMotor(int power) {
            m_basicMotor.controlMotor(power);
        }

        /**
         * Set the power level 0%-100% to be applied to the motor
         *
         * @param power new motor power 0-100
         */
        void setPower(unsigned int power) override;

        /**
         * Returns the current motor power setting.
         *
         * @return current power 0-100
         */
        unsigned int getPower() const override;

        /**
          * Causes motor to rotate forward until <code>stop()</code> or <code>flt()</code> is called.
          */
        void forward() override;

        /**
         * Causes motor to rotate backwards until <code>stop()</code> or <code>flt()</code> is called.
         */
        void backward() override;

        /**
         * Causes motor to stop immediately. It will resist any further motion. Cancels any rotate() orders in progress.
         */
        void stop() override;

        /**
         * Motor loses all power, causing the rotor to float freely to a stop.
         * This is not the same as stopping, which locks the rotor.
         */
        void flt() override;

        /**
         * Return <code>true</code> if the motor is moving.
         *
         * @return <code>true</code> if the motor is currently in motion, <code>false</code> if stopped.
         */
        bool isMoving() override;

        /**
         * returns tachometer count
         */
        int getTachoCount() const override;

        /**
         * resets the tachometer count to 0;
         */
        void resetTachoCount() override;
    };
}
