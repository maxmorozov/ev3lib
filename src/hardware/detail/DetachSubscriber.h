#pragma once

#include <utils/utilities.h>
#include <cstddef>
#include <memory>

namespace ev3lib::hardware::detail {

	struct DetachSubscriber : public utils::destructible {
		virtual void detach() = 0;
	};

}
