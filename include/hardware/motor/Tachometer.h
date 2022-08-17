/*
 * Tachometer.h
 */

#pragma once

#include "utils/utilities.h"

namespace ev3lib::hardware::motor {

	struct Tachometer : public utils::destructible {
		/**
		 * returns tachometer count
		 */
		virtual int getTachoCount() const = 0;

		/**
		 * resets the tachometer count to 0;
		 */
		virtual void resetTachoCount() = 0;
	};


}
