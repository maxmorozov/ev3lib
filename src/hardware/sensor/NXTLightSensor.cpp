/*
 * NXTLightSensor.cpp
 */

#include <stdexcept>
#include <hardware/sensor/NXTLightSensor.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::sensor {

    NXTLightSensor::NXTLightSensor(std::unique_ptr<port::AnalogPort> port)
            : AnalogSensor(std::move(port)) {

    }

    void NXTLightSensor::setFloodlight(bool floodlight) {
        switchType(floodlight ? port::SensorType::LIGHT_ACTIVE : port::SensorType::LIGHT_INACTIVE);
        this->floodlight = floodlight;

    }


} /* namespace ev3lib */
