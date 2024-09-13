/*
 * UIManager.h
 */

#pragma once

#include <utils/utilities.h>

namespace ev3lib::hardware::detail {

    struct UIManager: utils::destructible {
        /**
         * Returns true if the specified button is down
         */
        virtual bool checkButton(size_t buttonNo) const = 0;
    };

} /* namespace ev3lib::hardware::detail */
