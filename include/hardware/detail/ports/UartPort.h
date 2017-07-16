#ifndef EV3LIB_PORTS_UART_PORT_H_
#define EV3LIB_PORTS_UART_PORT_H_

#include <utilities.h>
#include <stddef.h>
#include <memory>
#include "MultiModePort.h"

namespace ev3lib {
namespace hardware {
namespace detail {

	struct UartPort: public MultiModePort {
	    /**
	     * read a number of bytes from the device
	     * @param buffer byte array to accept the data
	     * @param offset offset (in bytes) at which to store the data
	     * @param len number of bytes to read
	     */
	    virtual void read(uint8_t* buffer, size_t offset, size_t len) = 0;

	    /**
	     * Write bytes to the sensor
	     * @param buffer bytes to be written
	     * @param offset offset to the start of the write
	     * @param len length of the write
	     * @return number of bytes written
	     */
	    virtual int write(const uint8_t* buffer, size_t offset, size_t len) = 0;

	    /**
	     * Get the string name of the specified mode.<p><p>
	     * @param mode mode to lookup
	     * @return String version of the mode name
	     */
	    virtual std::string getModeName(size_t mode) const = 0;

		/**
		 * Reset the attached sensor. Following this the sensor must be initialized
		 * before it can be used.
		 */
		virtual void resetSensor() = 0;
	};


}}}


#endif /* EV3LIB_PORTS_UART_PORT_H_ */

