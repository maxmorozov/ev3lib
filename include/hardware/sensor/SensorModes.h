#pragma once

#include <utils/utilities.h>
#include <vector>
#include <string>

#include <hardware/sensor/SensorMode.h>

namespace ev3lib::hardware::sensor {

	/**
	 * Provide access to the modes supported by a sensor
	 * @author andy
	 *
	 */
	struct SensorModes : public SensorMode {
	    /**
	     * Return a list of string descriptions for the sensors available modes.
	     * @return list of string descriptions
	     */
		virtual std::vector<std::string> getAvailableModes() const = 0;

	    /**
	     * Sets the current mode for fetching samples
	     * @param mode the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
	     */
		virtual void setCurrentMode(size_t mode) = 0;

	    /**
	     * Sets the current mode for fetching samples
	     * @param modeName the name of the mode. name corresponds with the item value of the list from getAvailableModes().
	     */
		virtual void setCurrentMode(const std::string& modeName) = 0;

	    /** Gets the index number of the current mode.
	     * @return the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
	     */
		virtual size_t getCurrentMode() const = 0;

	    /** Gets the number of supported modes
	     * @return the number of supported modes
	     */
		virtual size_t getModeCount() const = 0;
	};

}
