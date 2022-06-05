/*
 * NXTLightSensor.cpp
 */

#include <stdexcept>
#include <hardware/sensor/NXTLightSensor.h>
#include "hardware/ports/SensorType.h"

namespace ev3lib::hardware {

NXTLightSensor::NXTLightSensor(std::unique_ptr<ports::AnalogPort> port)
	: AnalogSensor(std::move(port))
{

}

void NXTLightSensor::setFloodlight(bool floodlight)
{
    switchType(floodlight ? ports::SensorType::LIGHT_ACTIVE : ports::SensorType::LIGHT_INACTIVE);
    this->floodlight = floodlight;

}


} /* namespace ev3lib */
