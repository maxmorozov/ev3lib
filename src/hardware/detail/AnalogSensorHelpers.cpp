/*
 * AnalogSensorHelpers.cpp
 */

#include <cmath>
#include "EV3SensorConstants.h"
#include "AnalogSensorHelpers.h"

namespace ev3lib::hardware::detail {

    /**
     * Helper method. Take a voltage and return it as a normalized value in the
     * range 0.0-1.0
     * @param val input value
     * @return normalized value
     */
    float AnalogSensorHelpers::normalize(float val) {
        return val / EV3SensorConstants::ADC_REF;
    }

    /**
     * Return the equivalent NXT RAW sensor reading to the given voltage
     * @param val RAW ADC voltage
     * @return The reading that would be returned on the NXT
     */
    float AnalogSensorHelpers::NXTRawValue(short val) {
        return val * EV3SensorConstants::NXT_ADC_RES / EV3SensorConstants::ADC_RES;
    }

    /**
     * Return the equivalent NXT RAW sensor reading to the given voltage
     * @param val RAW ADC voltage
     * @return The reading that would be returned on the NXT
     */
    int AnalogSensorHelpers::NXTRawIntValue(short val) {
        return std::lround(NXTRawValue(val));
    }

} /* namespace ev3lib::hardware::detail */
