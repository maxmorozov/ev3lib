/*
 * ev3_device.cpp
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */
#include <fcntl.h>
#include <hardware/detail/ev3_device.h>
#include <hardware/detail/lms2012/lms2012.h>

namespace ev3lib {
namespace hardware {
namespace detail {

template<>
handle ev3device<handle_type::pwm_motor>::create_device()
{
	// Open the handle for writing commands
	return handle(PWM_DEVICE_NAME, O_WRONLY);
}

template<>
handle ev3device<handle_type::motor_encoder>::create_device()
{
    // Open the handle for reading motor values - shared memory
	return handle(MOTOR_DEVICE_NAME, O_RDWR | O_SYNC);
}


}}}



