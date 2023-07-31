#pragma once

#include <cstddef>
#include <memory>
#include <utils/utilities.h>

namespace ev3lib::hardware::port {

    struct MultiModePort: public utils::destructible {
        //Valid mode index range is 0..7, value -1 is reserved for RAW UART mode
        using mode_type = int8_t;

	    /**
	     * Get the current operating mode of the sensor
	     * @return the current mode
	     */
	    virtual mode_type getMode() const = 0;

	    /**
	     * Set the current operating mode for the sensor attached to the port.
	     * @param mode the new mode
	     * @return true if the mode has been accepted
	     */
        [[nodiscard]]
	    virtual bool setMode(mode_type mode) = 0;

	    /**
	     * Returns number of supported modes
	     *
	     * @return number of available modes
	     */
	    virtual size_t getModeCount() const = 0;
	};


}
