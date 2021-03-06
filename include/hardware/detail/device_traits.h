/*
 * device_traits.h
 *
 *  Created on: 07 ���. 2014 �.
 *      Author: Max
 */

#ifndef EV3_DEVICE_TRAITS_H_
#define EV3_DEVICE_TRAITS_H_

#include <fcntl.h>
#include <hardware/detail/lms2012/ev3_constants.h>
#include <hardware/detail/lejos/motor_data.h>

#define LEJOS

namespace ev3lib {
namespace hardware {
namespace detail {

	//EV3 hardware type
	enum class device_type {
		dcm,
		pwm_motor,
		motor_encoder,
		uart_sensor,
		i2c_sensor,
		analog_sensor,
		ui
	};

	template<device_type type>
	struct device_traits {
	};

	template<>
	struct device_traits<device_type::dcm> {
		static constexpr const char* device_name = lms2012::DCM_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::pwm_motor> {
		static const size_t ports_count = lms2012::vmOUTPUTS;

		static constexpr const char* device_name = lms2012::PWM_DEVICE_NAME;
		static const int device_flags = O_RDWR;
	};

	template<>
	struct device_traits<device_type::motor_encoder> {
		static const size_t ports_count = lms2012::vmOUTPUTS;

#ifdef LEJOS
		typedef lejos::MOTORSHARED device_map_type;
#else
		typedef lms2012::MOTORDATA device_map_type;
#endif

		static const size_t sensor_data_size = ports_count * sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::MOTOR_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::uart_sensor> {
		static const size_t ports_count = lms2012::vmINPUTS;

		typedef lms2012::UART device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::UART_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::i2c_sensor> {
		static const size_t ports_count = lms2012::vmINPUTS;

		//typedef UART device_map_type;

		//static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::IIC_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::analog_sensor> {
		static const size_t ports_count = lms2012::vmINPUTS;

		typedef lms2012::ANALOG device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::ANALOG_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::ui> {
		static const size_t ports_count = 1;

		typedef lms2012::UI device_map_type;

		static const size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::UI_DEVICE_NAME;
		static const int device_flags = O_RDWR | O_SYNC;
	};

}}}



#endif /* EV3_DEVICE_TRAITS_H_ */
