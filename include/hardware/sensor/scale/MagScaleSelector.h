#pragma once

#include <utils/utilities.h>

namespace ev3lib {
namespace hardware {

	struct MagScaleSelector : public destructible {
		/**
		 * Changes the magnetometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setMagnetometerScale(size_t scaleNo) = 0;

		/**
		 * Returns number of supported scales
		 *
		 * @return number of scales supported by the sensor
		 */
		virtual size_t getMagnetometerScales() const = 0;
	};


}}
