#pragma once

#include <span>
#include <hardware/port/MultiModePort.h>

namespace ev3lib::hardware::port {

	struct UartPort: MultiModePort {
	    /**
	     * read a number of bytes from the device
	     * @param buffer byte buffer to accept the data
	     */
	    virtual void read(std::span<uint8_t> buffer) = 0;

	    /**
	     * Write bytes to the sensor
	     * @param buffer bytes to be written
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
