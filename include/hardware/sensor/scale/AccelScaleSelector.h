#pragma once

#include <utils/utilities.h>

namespace ev3lib::hardware::sensor::scale {

	struct AccelScaleSelector : public utils::destructible {
		/**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setAccelerometerScale(size_t scaleNo) = 0;

		/**
		 * Returns number of supported scales
		 *
		 * @return number of scales supported by the sensor
		 */
		virtual size_t getAccelerometerScales() const = 0;
	};


}
