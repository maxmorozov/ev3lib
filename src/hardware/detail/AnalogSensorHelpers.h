/*
 * AnalogSensorHelpers.h
 */

#ifndef ANALOGSENSORHELPERS_H_
#define ANALOGSENSORHELPERS_H_

namespace ev3lib::hardware::detail {

class AnalogSensorHelpers {
public:
    AnalogSensorHelpers() = delete;
    ~AnalogSensorHelpers() = delete;

    /**
     * Helper method. Take a voltage and return it as a normalized value in the
     * range 0.0-1.0
     * @param val input value
     * @return normalized value
     */
    static float normalize(float val);

    /**
     * Return the equivalent NXT RAW sensor reading to the given voltage
     * @param val ADC voltage
     * @return The reading that would be returned on the NXT
     */
    static float NXTRawValue(float val);

    /**
     * Return the equivalent NXT RAW sensor reading to the given voltage
     * @param raw ADC voltage
     * @return The reading that would be returned on the NXT
     */
    static int NXTRawValue(int val);

    /**
     * Return the equivalent NXT RAW sensor reading to the given voltage
     * @param val ADC voltage
     * @return The reading that would be returned on the NXT
     */
    static int NXTRawIntValue(float val);

};

} /* namespace ev3lib::hardware::detail */

#endif /* ANALOGSENSORHELPERS_H_ */
