#pragma once

#include <utils/utilities.h>
#include <cstddef>
#include <memory>

namespace ev3lib::hardware::detail {

    struct DetachSubscriber: utils::destructible {
        virtual void detach() = 0;
    };

}
