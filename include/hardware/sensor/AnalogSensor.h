/*
 * AnalogSensor.h
 */

#pragma once

#include <memory>
#include <hardware/detail/SensorsManager.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::sensor {

/**
 * Returns raw ADC output value
 */
class AnalogSensor: public utils::destructible, utils::noncopyable {
protected:
	std::unique_ptr<port::AnalogPort> m_port;
    port::SensorType m_currentType = port::SensorType::NO_DATA;

    void switchType(port::SensorType newType);

public:
	explicit AnalogSensor(std::unique_ptr<port::AnalogPort> port) ;

    short getData() const;
};

} /* namespace ev3lib::hardware */
