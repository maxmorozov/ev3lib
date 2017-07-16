#pragma once

#include <utilities.h>

namespace ev3lib {
namespace hardware {

	struct GyroScaleSelector : public destructible {
		/**
		 * Changes the gyroscope full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setGyroscopeScale(size_t scaleNo) = 0;
	};


}}
