//
// TachoMotorPort.h
//

#pragma once

#include <hardware/port/BasicMotorPort.h>
#include <robotics/Encoder.h>

namespace ev3lib::hardware::port {

    /**
     * Abstraction for a motor port that supports NXT and EV3 motors with tachometers.
     *
     * @author Lawrie Griffiths
     */
    struct TachoMotorPort: BasicMotorPort, robotics::Encoder {
    };

}
