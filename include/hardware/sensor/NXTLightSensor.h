/*
 * NXTLightSensor.h
 */

#pragma once

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
	 *
	 * @param floodLight new light source state
	 */
	void setFloodlight(bool floodLight);

    /**
     * Gets the current status of the onboard light source
     * @return true if the light source if turned on
     */
    bool isFloodlight() const;
};

} /* namespace ev3lib::hardware */
