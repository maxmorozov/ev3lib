/*
 * NXTLightSensor.h
 */

#ifndef EV3LIB_NXT_LIGHT_SENSOR_H_
#define EV3LIB_NXT_LIGHT_SENSOR_H_

#include <hardware/sensor/AnalogSensor.h>

namespace ev3lib::hardware::sensor {

/**
 * Returns raw ADC output value
 */
class NXTLightSensor : public AnalogSensor {
private:
	bool floodlight = false;

public:
	explicit NXTLightSensor(std::unique_ptr<port::AnalogPort> port);

	/**
	 * Turns onboard light source of the sensor on or off
	 */
	void setFloodlight(bool floodlight);
};

} /* namespace ev3lib::hardware */

#endif /* EV3LIB_NXT_LIGHT_SENSOR_H_ */
