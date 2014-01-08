/*
 * device_traits.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3_DEVICE_TRAITS_H_
#define EV3_DEVICE_TRAITS_H_

#include <fcntl.h>
#include <hardware/detail/lms2012/lms2012.h>

namespace ev3lib {
namespace hardware {
namespace detail {

	//EV3 hardware type
	enum class device_type {
		pwm_motor,
		motor_encoder,
		uart_sensor,
		i2c_sensor,
		analog_sensor
	};

	template<device_type type>
	struct device_traits {
	};

	template<>
	struct device_traits<device_type::pwm_motor> {
		static const size_t ports_count = vmOUTPUTS;

		static constexpr const char* device_name = PWM_DEVICE_NAME;
		static const int device_flags = O_WRONLY;
	};

	template<>
	struct device_traits<device_type::motor_encoder> {
		static const size_t ports_count = vmOUTPUTS;

		typedef MOTORDATA device_map_type;

		static const size_t sensor_data_size = ports_count * sizeof(device_map_type);

		static constexpr const char* device_name = MOTOR_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;

	};

	template<>
	struct device_traits<device_type::uart_sensor> {
		static const size_t ports_count = vmINPUTS;

		typedef UART device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = UART_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::i2c_sensor> {
		static const size_t ports_count = vmINPUTS;

		typedef UART device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = IIC_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::analog_sensor> {
		static const size_t ports_count = vmINPUTS;

		typedef ANALOG device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = ANALOG_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

}}}



#endif /* EV3_DEVICE_TRAITS_H_ */
