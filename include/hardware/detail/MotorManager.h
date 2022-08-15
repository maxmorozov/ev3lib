/*
 * MotorManager.h
 */

#pragma once

#include <utils/utilities.h>
#include <hardware/port/TachoMotorPort.h>

namespace ev3lib::hardware::detail {

	/**
	 * Manages EV3 motor port connections
	 */
	struct MotorManager: public destructible {
		/**
		 * Returns internal motor port structure. The clients should not delete it
		 */
		virtual port::TachoMotorPort* getMotorPort(size_t port) = 0;
	};

}
