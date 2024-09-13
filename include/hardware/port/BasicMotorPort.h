#pragma once

#include <utils/utilities.h>

namespace ev3lib::hardware::port {

    enum class PWMMode: int {
        Float = 0, //Motor is not driven during off phase of PWM
        Brake = 1  //Motor is driven during off phase of PWM
    };

    enum class MotorCommand: int {
        Forward = 1,  // Motor is running forward
        Backward = 2, // Motor is running backwards
        Stop = 3,     // Motor is stopped (PWM drive still applied)
        Float = 4     // Motor is floating (no PWM drive)
    };

    /**
     * An abstraction for a motor port that supports RCX
     * type motors, but not NXT and EV3 motors with tachometers.
     *
     * @author Lawrie Griffiths.
     */
    struct BasicMotorPort: utils::destructible {
        /** Maximum power setting = 100% */
        static const int MAX_POWER = 100;

        /**
         * Starts and stops the motor
         */
        virtual void controlMotor(unsigned int power, MotorCommand command) = 0;
    };

}
