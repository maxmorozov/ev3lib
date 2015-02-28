/*
 * UIManager.h
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3LIB_UIMANAGER_H_
#define EV3LIB_UIMANAGER_H_

#include <utilities.h>

namespace ev3lib {
namespace hardware {
namespace detail {

struct UIManager : public destructible {
	/**
	 * Returns true if the specified button is down
	 */
	virtual bool checkButton(size_t buttonNo) const = 0;
};

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_UIMANAGER_H_ */
