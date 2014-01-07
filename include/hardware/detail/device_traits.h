/*
 * device_traits.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3_DEVICE_TRAITS_H_
#define EV3_DEVICE_TRAITS_H_

#include <hardware/detail/lms2012/lms2012.h>

namespace ev3lib {
namespace hardware {
namespace detail {

	//EV3 hardware type
	enum class handle_type {
		pwm_motor,
		motor_encoder
	};

	template<handle_type type>
	struct device_traits {
	};

	template<>
	struct device_traits<handle_type::pwm_motor> {
		static const size_t ports_count = vmOUTPUTS;

		typedef MOTORDATA device_map_type;
	};

	template<>
	struct device_traits<handle_type::motor_encoder> {
		static const size_t ports_count = vmOUTPUTS;

		typedef MOTORDATA device_map_type;
	};

}}}



#endif /* EV3_DEVICE_TRAITS_H_ */
