/*
 * AnalogSensor.h
 */

#ifndef EV3LIB_ANALOGSENSOR_H_
#define EV3LIB_ANALOGSENSOR_H_

#include <memory>
#include <hardware/detail/SensorsManager.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::sensor {

/**
 * Returns raw ADC output value
 */
class AnalogSensor : public destructible, noncopyable {
protected:
	std::unique_ptr<port::AnalogPort> m_port;
    port::SensorType m_currentType = port::SensorType::NO_DATA;

protected:
	void switchType(port::SensorType newType);

public:
	explicit AnalogSensor(std::unique_ptr<port::AnalogPort> port) ;

	int getData() const;
};

} /* namespace ev3lib::hardware */

#endif /* EV3LIB_ANALOGSENSOR_H_ */
