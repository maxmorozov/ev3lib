/*
 * EV3Battery.h
 */

#pragma once

#include <hardware/detail/Power.h>
#include <hardware/detail/BatteryManager.h>

namespace ev3lib::hardware::detail {

class EV3Battery : public Power {
protected:
    constexpr static float SHUNT_IN = 0.05f;     //  [Ohm]
    constexpr static float AMP_CIN = 15.0f;      //  [Times]
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
    static float convert(short val);

public:
	explicit EV3Battery(BatteryManager* manager);

	/**
	 * The NXT uses 6 batteries of 1500 mV each.
	 * @return Battery voltage in mV. ~9000 = full.
	 */
	int getVoltageMilliVolt() const override;

	/**
	 * The NXT uses 6 batteries of 1.5 V each.
	 * @return Battery voltage in Volt. ~9V = full.
	 */
	float getVoltage() const override;

	/**
	 * Return the current draw from the battery
	 * @return current in Amps
	 */
	float getBatteryCurrent() const override;

	/**
	 * return the motor current draw
	 * @return current in Amps
	 */
	float getMotorCurrent() const override;

};

}
