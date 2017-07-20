/*
 * EV3Battery.cpp
 */

#include "EV3Battery.h"
#include "EV3SensorConstants.h"

namespace ev3lib {
namespace hardware {
namespace detail {

EV3Battery::EV3Battery(BatteryManager* manager)
	: m_manager(manager)
{

}

/**
 * Convert from ADC reading to actual units.
 * @param val
 * @return
 */
float EV3Battery::convert(int val)
{
    return val * EV3SensorConstants::ADC_REF / EV3SensorConstants::ADC_RES;
}

/**
 * The NXT uses 6 batteries of 1500 mV each.
 * @return Battery voltage in mV. ~9000 = full.
 */
int EV3Battery::getVoltageMilliVolt() const {
    return (int)(getVoltage() * 1000.0f);
}

/**
 * The NXT uses 6 batteries of 1.5 V each.
 * @return Battery voltage in Volt. ~9V = full.
 */
float EV3Battery::getVoltage() const {
    float CinV = convert(m_manager->getBatteryCurrent()) / AMP_CIN;
    return convert(m_manager->getBatteryVoltage()) / AMP_VIN + CinV + VCE;
}

/**
 * Return the current draw from the battery
 * @return current in Amps
 */
float EV3Battery::getBatteryCurrent() const {
    return (convert(m_manager->getBatteryCurrent()) / AMP_CIN) / SHUNT_IN;
}

/**
 * return the motor current draw
 * @return current in Amps
 */
float EV3Battery::getMotorCurrent() const {
    return (convert(m_manager->getMotorCurrent()) / AMP_COUT) / SHUNT_OUT;
}

}}}
