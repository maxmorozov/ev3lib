/*
 * EV3SensorConstants.h
 */

#pragma once

#include <hardware/detail/lms2012/ev3_constants.h>

namespace ev3lib::hardware::detail {

class EV3SensorConstants {
public:
	static const int SENSORS = lms2012::INPUTS;
	static const int MOTORS = lms2012::OUTPUTS;

	static constexpr float ADC_REF = lms2012::ADC_REF / 1000.0f; //5 V
	static const int ADC_RES = lms2012::ADC_RES;

	/** MAX value returned as a RAW sensor reading for standard NXT A/D sensors */
	static const int NXT_ADC_RES = 1023;

};

} /* namespace ev3lib::hardware::detail */

