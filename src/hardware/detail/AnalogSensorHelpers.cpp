/*
 * AnalogSensorHelpers.cpp
 *
 *  Created on: 23 февр. 2015 г.
 *      Author: Max
 */

#include "EV3SensorConstants.h"
#include "AnalogSensorHelpers.h"

namespace ev3lib {
namespace hardware {
namespace detail {

/**
 * Helper method. Take a voltage and return it as a normalized value in the
 * range 0.0-1.0
 * @param val input value
 * @return normalized value
 */
float AnalogSensorHelpers::normalize(float val)
{
	return val/EV3SensorConstants::ADC_REF;
}

/**
 * Return the equivalent NXT RAW sensor reading to the given voltage
 * @param val ADC voltage
 * @return The reading that would be returned on the NXT
 */
float AnalogSensorHelpers::NXTRawValue(float val)
{
    return val * EV3SensorConstants::NXT_ADC_RES / EV3SensorConstants::ADC_REF;
}

/**
 * Return the equivalent NXT RAW sensor reading to the given voltage
 * @param val ADC voltage
 * @return The reading that would be returned on the NXT
 */
int AnalogSensorHelpers::NXTRawIntValue(float val)
{
	return (int)(NXTRawValue(val) + 0.5f);
}

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
