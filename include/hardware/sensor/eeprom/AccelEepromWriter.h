#pragma once

#include <utils/utilities.h>

namespace ev3lib {
namespace hardware {

	struct AccelEepromWriter : public destructible {
		/**
		 * Update accelerometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @return true if the EEPROM data has been successfully written
		 */
		virtual bool writeAccelerometerEeprom(size_t scaleNo, gsl::span<const int16_t> data) = 0;
	};


}}
