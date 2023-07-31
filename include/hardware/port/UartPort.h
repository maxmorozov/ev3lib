#pragma once

#include <cstddef>
#include <memory>
#include <span>
#include <utils/utilities.h>
#include <hardware/port/MultiModePort.h>

namespace ev3lib::hardware::port {

	struct UartPort: public MultiModePort {
	    /**
	     * read a number of bytes from the device
	     * @param buffer byte array to accept the data
	     * @param offset offset (in bytes) at which to store the data
	     * @param len number of bytes to read
	     */
	    virtual void read(std::span<uint8_t> buffer) = 0;

	    /**
	     * Write bytes to the sensor
	     * @param buffer bytes to be written
	     * @param offset offset to the start of the write
	     * @param len length of the write
	     * @return number of bytes written
	     */
	    virtual ssize_t write(std::span<const uint8_t> buffer) = 0;

	    /**
	     * Get the string name of the specified mode.<p><p>
	     * @param mode mode to lookup
	     * @return String version of the mode name
	     */
	    virtual std::string getModeName(mode_type mode) const = 0;

		/**
		 * Reset the attached sensor. Following this the sensor must be initialized
		 * before it can be used.
		 */
		virtual void resetSensor() = 0;
	};


}
