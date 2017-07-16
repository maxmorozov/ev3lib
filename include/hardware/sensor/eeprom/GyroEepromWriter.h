#pragma once

#include <utilities.h>

namespace ev3lib {
namespace hardware {

	struct GyroEepromWriter : public destructible {
		/**
		 * Update gyroscope EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
		virtual bool writeGyroscopeEeprom(size_t scaleNo, const int16_t* data, size_t size) = 0;
	};


}}
