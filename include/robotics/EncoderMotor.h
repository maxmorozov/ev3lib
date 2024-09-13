#pragma once

#include <robotics/DCMotor.h>
#include <robotics/Encoder.h>

namespace ev3lib::robotics {

    /**
     * An EncoderMotor is a platform independent interface for an <i>unregulated motor</i>
     * that also has basic tachometer functions.
     *
     * @author BB
     */
    struct EncoderMotor: DCMotor, Encoder {
        // no extra methods
    };

} // robotics
