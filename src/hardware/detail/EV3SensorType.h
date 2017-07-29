/*
 * SensorType.h
 */

#ifndef EV3LIB_EV3_SENSOR_TYPE_H_
#define EV3LIB_EV3_SENSOR_TYPE_H_


namespace ev3lib {
namespace hardware {
namespace detail {

	enum class EV3SensorType : int {
		NO_SENSOR,
		SWITCH,
		TEMPERATURE,
		REFLECTION,
		ANGLE,
		LIGHT_ACTIVE,
		LIGHT_INACTIVE,
		SOUND_DB,
		SOUND_DBA,
		CUSTOM,
		LOWSPEED,
		LOWSPEED_9V,
		HISPEED,
		COLORFULL,
		COLORRED,
		COLORGREEN ,
		COLORBLUE,
		COLORNONE,
		// additional leJOS types for the EV3
		HIGHSPEED,
		HIGHSPEED_9V
	};

}
}
}



#endif /* EV3LIB_EV3_SENSOR_TYPE_H_ */
