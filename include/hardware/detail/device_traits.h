/*
 * device_traits.h
 */

#pragma once

#include <fcntl.h>
#include <hardware/detail/lms2012/ev3_constants.h>
#include <hardware/detail/lejos/motor_data.h>

#define LEJOS

namespace ev3lib::hardware::detail {

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
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::pwm_motor> {
		static constexpr size_t ports_count = lms2012::vmOUTPUTS;

		static constexpr const char* device_name = lms2012::PWM_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR;
	};

	template<>
	struct device_traits<device_type::motor_encoder> {
		static constexpr size_t ports_count = lms2012::vmOUTPUTS;

#ifdef LEJOS
		using device_map_type = volatile lejos::MOTORSHARED;
#else
        using device_map_type = volatile lms2012::MOTORDATA;
#endif

		static constexpr size_t sensor_data_size = ports_count * sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::MOTOR_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::uart_sensor> {
		static constexpr size_t ports_count = lms2012::vmINPUTS;

		using device_map_type = volatile lms2012::UART;

		static constexpr size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::UART_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::i2c_sensor> {
		static constexpr size_t ports_count = lms2012::vmINPUTS;

		static constexpr const char* device_name = lms2012::IIC_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::analog_sensor> {
		static constexpr size_t ports_count = lms2012::vmINPUTS;

		using device_map_type = volatile lms2012::ANALOG;

		static constexpr size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::ANALOG_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

	template<>
	struct device_traits<device_type::ui> {
		static constexpr size_t ports_count = 1;

		using device_map_type = volatile lms2012::UI;

		static constexpr size_t sensor_data_size = sizeof(device_map_type);

		static constexpr const char* device_name = lms2012::UI_DEVICE_NAME;
		static constexpr int device_flags = O_RDWR | O_SYNC;
	};

}
