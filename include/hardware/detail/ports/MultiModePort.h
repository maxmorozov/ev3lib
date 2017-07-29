#ifndef EV3LIB_PORTS_MULTIMODE_PORT_H_
#define EV3LIB_PORTS_MULTIMODE_PORT_H_

#include <utils/utilities.h>
#include <stddef.h>
#include <memory>

namespace ev3lib {
namespace hardware {
namespace detail {

	struct MultiModePort: public destructible {
	    /**
	     * Get the current operating mode of the sensor
	     * @return the current mode
	     */
	    virtual size_t getMode() const = 0;

	    /**
	     * Set the current operating mode for the sensor attached to the port.
	     * @param mode the new mode
	     * @return true if the mode has been accepted
	     */
	    virtual bool setMode(size_t mode) = 0;

	    /**
	     * Returns numner of supported modes
	     *
	     * @return number of available modes
	     */
	    virtual size_t getModeCount() const = 0;
	};


}}}


#endif /* EV3LIB_PORTS_MULTIMODE_PORT_H_ */

