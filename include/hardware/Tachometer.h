/*
 * Tachometer.h
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3LIB_TACHOMETER_H_
#define EV3LIB_TACHOMETER_H_

#include <hardware/detail/utilities.h>

namespace ev3lib {
namespace hardware {

	struct Tachometer : public detail::destructible {
		/**
		 * returns tachometer count
		 */
		virtual int getTachoCount() const = 0;

		/**
		 * resets the tachometer count to 0;
		 */
		virtual void resetTachoCount() = 0;
	};


} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_TACHOMETER_H_ */
