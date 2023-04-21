/*
 * BatteryManager.h
 */

#pragma once

namespace ev3lib::hardware::detail {

/**
 * Provides information about battery state
 */
struct BatteryManager: public utils::destructible {
	/**
	 * Battery voltage
	 */
	virtual short getBatteryVoltage() const = 0;

	/**
	 * Current flowing from the battery
	 */
	virtual short getMotorCurrent() const = 0;

	/**
	 * Current flowing from the battery
	 */
	virtual short getBatteryCurrent() const = 0;
};

} /* namespace ev3lib::hardware::detail */
