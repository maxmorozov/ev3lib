/*
 * Power.h
 *
 *  Created on: 28 февр. 2015 г.
 *      Author: Max
 */

#ifndef POWER_H_
#define POWER_H_

#include <utilities.h>

namespace ev3lib {
namespace hardware {
namespace detail {

/**
 * Interface used to access information about the EV3 battery and current usage.
 * @author Brian Bagnall, Lawrie Griffiths Andy Shaw
 *
 */
struct Power : public destructible {

	/**
	 * The NXT uses 6 batteries of 1500 mV each.
	 * @return Battery voltage in mV. ~9000 = full.
	 */
	virtual int getVoltageMilliVolt() const = 0;

	/**
	 * The NXT uses 6 batteries of 1.5 V each.
	 * @return Battery voltage in Volt. ~9V = full.
	 */
	virtual float getVoltage() const = 0;

	/**
	 * Return the current draw from the battery
	 * @return current in Amps
	 */
	virtual float getBatteryCurrent() const = 0;

	/**
	 * return the motor current draw
	 * @return current in Amps
	 */
	virtual float getMotorCurrent() const = 0;
};

}}}

#endif /* POWER_H_ */
