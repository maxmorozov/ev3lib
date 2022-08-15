#pragma once

#include <utils/utilities.h>

namespace ev3lib::robotics {
    /**
     * Abstraction for the tachometer built into NXT motors.
     *
     * @author Lawrie Griffiths
     */
    struct Encoder: public destructible {
        /**
         * Returns the tachometer count.
         *
         * @return tachometer count in degrees
         */
        virtual int getTachoCount() const = 0;

        /**
         * Reset the tachometer count.
         */
        virtual void resetTachoCount() = 0;
    };

}