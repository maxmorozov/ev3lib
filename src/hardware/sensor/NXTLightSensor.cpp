/*
 * NXTLightSensor.cpp
 */

#include <utility>
#include <hardware/sensor/NXTLightSensor.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::sensor {

    NXTLightSensor::NXTLightSensor(std::unique_ptr<port::AnalogPort> port)
            : AnalogSensor(std::move(port)) {

    }

    void NXTLightSensor::setFloodlight(bool floodLight) {
        switchType(floodLight ? port::SensorType::LIGHT_ACTIVE : port::SensorType::LIGHT_INACTIVE);
        floodlight = floodLight;
    }

    bool NXTLightSensor::isFloodlight() const {
        return floodlight;
    }


} /* namespace ev3lib */
