/*
 * EV3Battery.h
 *
 *  Created on: 28 ����. 2015 �.
 *      Author: Max
 */

#ifndef EV3BATTERY_H_
#define EV3BATTERY_H_

#include <hardware/detail/Power.h>
#include <hardware/detail/BatteryManager.h>

namespace ev3lib {
namespace hardware {
namespace detail {

class EV3Battery : public Power {
protected:
    constexpr static float SHUNT_IN = 0.11f;     //  [Ohm]
    constexpr static float AMP_CIN = 22.0f;      //  [Times]
    constexpr static float SHUNT_OUT = 0.055f;   //  [Ohm]
    constexpr static float AMP_COUT = 19.0f;     //  [Times]
    constexpr static float VCE = 0.05f;          //  [V]
    constexpr static float AMP_VIN = 0.5f;       //  [Times]

    BatteryManager* m_manager;

    /**
     * Convert from ADC reading to actual units.
     * @param val
     * @return
     */
    static float convert(int val);

public:
	EV3Battery(BatteryManager* manager);

	/**
	 * The NXT uses 6 batteries of 1500 mV each.
	 * @return Battery voltage in mV. ~9000 = full.
	 */
	virtual int getVoltageMilliVolt() const override;

	/**
	 * The NXT uses 6 batteries of 1.5 V each.
	 * @return Battery voltage in Volt. ~9V = full.
	 */
	virtual float getVoltage() const override;

	/**
	 * Return the current draw from the battery
	 * @return current in Amps
	 */
	virtual float getBatteryCurrent() const override;

	/**
	 * return the motor current draw
	 * @return current in Amps
	 */
	virtual float getMotorCurrent() const override;

};

}}}

#endif /* EV3BATTERY_H_ */
