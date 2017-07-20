/*
 * Battery.cpp
 */

#include <hardware/Battery.h>

namespace ev3lib {
namespace hardware {

Battery::Battery(detail::Power* power)
	: m_power(power)
{

}

/**
 * The NXT uses 6 batteries of 1500 mV each.
 * @return Battery voltage in mV. ~9000 = full.
 */
int Battery::getVoltageMilliVolt() const {
	return m_power->getVoltageMilliVolt();
}

/**
 * The NXT uses 6 batteries of 1.5 V each.
 * @return Battery voltage in Volt. ~9V = full.
 */
float Battery::getVoltage() const {
	return m_power->getVoltage();
}

/**
 * Return the current draw from the battery
 * @return current in Amps
 */
float Battery::getBatteryCurrent() const {
	return m_power->getBatteryCurrent();
}

/**
 * return the motor current draw
 * @return current in Amps
 */
float Battery::getMotorCurrent() const {
	return m_power->getMotorCurrent();
}

} /* namespace hardware */
} /* namespace ev3lib */
