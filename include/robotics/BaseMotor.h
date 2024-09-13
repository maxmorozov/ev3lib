#pragma once

#include <utils/utilities.h>

namespace ev3lib::robotics {
    /**
     * Base motor interface. Contains basic movement commands.
     */
    struct BaseMotor: utils::destructible {

        /**
          * Causes motor to rotate forward until <code>stop()</code> or <code>flt()</code> is called.
          */
        virtual void forward() = 0;

        /**
         * Causes motor to rotate backwards until <code>stop()</code> or <code>flt()</code> is called.
         */
        virtual void backward() = 0;

        /**
         * Causes motor to stop immediately. It will resist any further motion. Cancels any rotate() orders in progress.
         */
        virtual void stop() = 0;

        /**
         * Motor loses all power, causing the rotor to float freely to a stop.
         * This is not the same as stopping, which locks the rotor.
         */
        virtual void flt() = 0;

        /**
         * Return <code>true</code> if the motor is moving.
         *
         * @return <code>true</code> if the motor is currently in motion, <code>false</code> if stopped.
         */
        virtual bool isMoving() = 0;
    };

}