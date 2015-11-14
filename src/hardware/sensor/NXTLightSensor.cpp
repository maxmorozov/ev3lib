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

NXTLightSensor::NXTLightSensor(NXTLightSensor&& other)
	: AnalogSensor(std::move(other)), floodlight(other.floodlight)
{

}


/**
 * Switch to the selected type (if not already in that type) and delay for the
 * specified period to allow the sensor to settle in the new state. <br>
 * NOTE: This method is intended for use with NXT sensor drivers that use a
 * sensor type to specify the operating mode.
 * @param newType The type to switch to.
 * @param switchDelay Time in mS to delay after the switch.
 */
void NXTLightSensor::switchType(int newType)
{
    if (currentType != newType)
    {
        if (!m_port->setType(newType))
            throw std::logic_error("Invalid sensor mode");
        currentType = newType;
    }
}

void NXTLightSensor::setFloodlight(bool floodlight)
{
    switchType(int(floodlight ? detail::EV3SensorType::LIGHT_ACTIVE : detail::EV3SensorType::LIGHT_INACTIVE));
    this->floodlight = floodlight;

}


} /* namespace hardware */
} /* namespace ev3lib */
