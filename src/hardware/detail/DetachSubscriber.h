#ifndef EV3_DETACH_SUBSCRIBER_H
#define EV3_DETACH_SUBSCRIBER_H

#include <utils/utilities.h>
#include <stddef.h>
#include <memory>

namespace ev3lib {
namespace hardware {
namespace detail {

	struct DetachSubscriber : public ev3lib::destructible {
		virtual void detach() = 0;
	};


}}}

#endif //EV3_DETACH_SUBSCRIBER_H
