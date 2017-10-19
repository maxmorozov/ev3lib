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
class AnalogSensor : public destructible, noncopyable {
protected:
	std::unique_ptr<detail::AnalogPort> m_port;
    int m_currentType = -1;

protected:
	void switchType(int newType);

public:
	explicit AnalogSensor(std::unique_ptr<detail::AnalogPort> port) ;

	int getData() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_ANALOGSENSOR_H_ */
