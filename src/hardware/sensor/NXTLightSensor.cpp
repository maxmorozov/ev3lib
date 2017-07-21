/*
 * NXTLightSensor.cpp
 */

#include <stdexcept>
#include <hardware/sensor/NXTLightSensor.h>
#include "../detail/EV3SensorType.h"

namespace ev3lib {
namespace hardware {

NXTLightSensor::NXTLightSensor(std::unique_ptr<detail::AnalogPort>&& port)
	: AnalogSensor(std::move(port))
{

}

NXTLightSensor::NXTLightSensor(NXTLightSensor&& other) noexcept
	: AnalogSensor(std::move(other)), floodlight(other.floodlight)
{

}


void NXTLightSensor::setFloodlight(bool floodlight)
{
    switchType(int(floodlight ? detail::EV3SensorType::LIGHT_ACTIVE : detail::EV3SensorType::LIGHT_INACTIVE));
    this->floodlight = floodlight;

}


} /* namespace hardware */
} /* namespace ev3lib */
