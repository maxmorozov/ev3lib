/*
 * AnalogSensor.h
 */

#ifndef EV3LIB_ANALOGSENSOR_H_
#define EV3LIB_ANALOGSENSOR_H_

#include <memory>
#include <hardware/detail/SensorsManager.h>

namespace ev3lib {
namespace hardware {

/**
 * Returns raw ADC output value
 */
class AnalogSensor {
protected:
	std::unique_ptr<detail::AnalogPort> m_port;
    int currentType = -1;

protected:
	void switchType(int newType);

public:
	AnalogSensor(std::unique_ptr<detail::AnalogPort>&& port);
	AnalogSensor(AnalogSensor&& other);
	virtual ~AnalogSensor();

	int getData() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_ANALOGSENSOR_H_ */
