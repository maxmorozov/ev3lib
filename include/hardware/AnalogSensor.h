/*
 * AnalogSensor.h
 *
 *  Created on: 23 марта 2015 г.
 *      Author: Max
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
private:
	std::unique_ptr<detail::AnalogPort> m_port;
public:
	AnalogSensor(std::unique_ptr<detail::AnalogPort>&& port);
	AnalogSensor(AnalogSensor&& other);
	virtual ~AnalogSensor();

	int getData() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_ANALOGSENSOR_H_ */
