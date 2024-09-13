#pragma once

#include <span>
#include <utils/utilities.h>

namespace ev3lib::hardware::sensor::eeprom {

	struct AccelEepromWriter: utils::destructible {
		/**
		 * Update accelerometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @return true if the EEPROM data has been successfully written
		 */
        [[nodiscard]]
		virtual bool writeAccelerometerEeprom(size_t scaleNo, std::span<const int16_t> data) = 0;
	};

}
