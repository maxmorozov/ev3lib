#pragma once

#include <utilities.h>

namespace ev3lib {
namespace hardware {

	struct AccelScaleSelector : public destructible {
		/**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setAccelerometerScale(size_t scaleNo) = 0;
	};


}}
