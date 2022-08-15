#pragma once

/*
 * SensorType.h
 */

namespace ev3lib::hardware::port {

    enum class SensorType : int {
        NO_SENSOR = 0,
        SWITCH = 1,
        TEMPERATURE = 2,
        REFLECTION = 3,
        ANGLE = 4,
        LIGHT_ACTIVE = 5,
        LIGHT_INACTIVE = 6,
        SOUND_DB = 7,
        SOUND_DBA = 8,
        CUSTOM = 9,
        LOWSPEED = 10,
        LOWSPEED_9V = 11,
        HISPEED = 12,
        COLORFULL = 13,
        COLORRED = 14,
        COLORGREEN = 15,
        COLORBLUE = 16,
        COLORNONE = 17,
        // additional leJOS types for the EV3
        HIGHSPEED = 18,
        HIGHSPEED_9V = 19,

        //Fake initial value
        NO_DATA = -1
    };

}
