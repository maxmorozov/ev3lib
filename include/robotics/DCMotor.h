#pragma once

#include <robotics/BaseMotor.h>

namespace ev3lib::robotics {

    /**
     * Interface for a regular DC motor.
     */
    struct DCMotor : public BaseMotor {
        /**
         * Set the power level 0%-100% to be applied to the motor
         *
         * @param power new motor power 0-100
         */
        virtual void setPower(unsigned int power) = 0;

        /**
         * Returns the current motor power setting.
         * 
         * @return current power 0-100
         */
        virtual unsigned int getPower() const = 0;
    };

}