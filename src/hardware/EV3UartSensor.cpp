/*
 * EV3UartSensor.cpp
 *
 *  Created on: 08 џэт. 2014 у.
 *      Author: Max
 */
#include <hardware/EV3UartSensor.h>

namespace ev3lib {
namespace hardware {

detail::EV3InputDevice<detail::device_type::uart_sensor> EV3UartSensor::m_device;

int EV3UartSensor::getValue() const {
	UART* uartData = m_device.getSensorData();
#ifndef DISABLE_FAST_DATALOG_BUFFER
	return uartData->Raw[m_port][uartData->Actual[m_port]][0];
#else
	return uartData->Raw[m_port][0];
#endif
}

}}



