#pragma once

#include <utils/utilities.h>

namespace ev3lib::hardware::sensor::eeprom {

	struct MagEepromWriter : public utils::destructible {
		/**
		 * Update magnetometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @return true if the EEPROM data has been successfully written
		 */
		virtual bool writeMagnetomtereEeprom(size_t scaleNo, gsl::span<const int16_t> data) = 0;
	};


}
