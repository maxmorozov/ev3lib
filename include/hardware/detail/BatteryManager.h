/*
 * BatteryManager.h
 */

#ifndef BATTERYMANAGER_H_
#define BATTERYMANAGER_H_

namespace ev3lib {
namespace hardware {
namespace detail {

/**
 * Provides information about battery state
 */
struct BatteryManager: public destructible {
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

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */

#endif /* BATTERYMANAGER_H_ */
