/*
 * Battery.h
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <hardware/detail/Power.h>
#include "detail/Power.h"

namespace ev3lib {
namespace hardware {

class Battery {
private:
	detail::Power* m_power;
public:
	Battery(detail::Power* power);

	/**
	 * The NXT uses 6 batteries of 1500 mV each.
	 * @return Battery voltage in mV. ~9000 = full.
	 */
	int getVoltageMilliVolt() const;

	/**
	 * The NXT uses 6 batteries of 1.5 V each.
	 * @return Battery voltage in Volt. ~9V = full.
	 */
	float getVoltage() const;

	/**
	 * Return the current draw from the battery
	 * @return current in Amps
	 */
	float getBatteryCurrent() const;

	/**
	 * return the motor current draw
	 * @return current in Amps
	 */
	float getMotorCurrent() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* BATTERY_H_ */
