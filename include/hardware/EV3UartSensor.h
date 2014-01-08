/*
 * EV3UartPort.h
 *
 *  Created on: 08 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_EV3UARTPORT_H_
#define EV3LIB_EV3UARTPORT_H_

#include <hardware/detail/ev3_device.h>

namespace ev3lib {
namespace hardware {

	class EV3UartSensor {
	private:
		static detail::EV3InputDevice<detail::device_type::uart_sensor> m_device;

		int m_port; //zero-based
	public:
		EV3UartSensor(int port): m_port(port) {}

		int getValue() const;
	};


}}



#endif /* EV3LIB_EV3UARTPORT_H_ */
