#ifndef EV3_DETACH_SUBSCRIBER_H
#define EV3_DETACH_SUBSCRIBER_H

#include <utils/utilities.h>
#include <cstddef>
#include <memory>

namespace ev3lib::hardware::detail {

	struct DetachSubscriber : public ev3lib::destructible {
		virtual void detach() = 0;
	};

}

#endif //EV3_DETACH_SUBSCRIBER_H
