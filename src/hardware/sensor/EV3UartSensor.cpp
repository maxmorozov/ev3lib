/*
 * EV3UartSensor.cpp
 *
 *  Created on: 08 џэт. 2014 у.
 *      Author: Max
 */
#include <hardware/sensor/EV3UartSensor.h>

namespace ev3lib {
namespace hardware {

typedef detail::EV3InputDevice<detail::device_type::uart_sensor> device_type;
device_type EV3UartSensor::m_device;

int EV3UartSensor::getValue() const {
	device_type::device_map_type* uartData = m_device.getSensorData();
#ifndef DISABLE_FAST_DATALOG_BUFFER
	return uartData->Raw[m_port][uartData->Actual[m_port]][0];
#else
	return uartData->Raw[m_port][0];
#endif
}

}}



