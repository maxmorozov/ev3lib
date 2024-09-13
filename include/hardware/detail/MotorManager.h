/*
 * MotorManager.h
 */

#pragma once

#include <cstdint>
#include <utils/utilities.h>
#include <hardware/port/TachoMotorPort.h>

namespace ev3lib::hardware::detail {

	/**
	 * Manages EV3 motor port connections
	 */
    struct MotorManager: utils::destructible {
		/**
		 * Returns internal motor port structure. The clients should not delete it
		 */
		virtual port::TachoMotorPort* getMotorPort(uint8_t port) = 0;
	};

}
