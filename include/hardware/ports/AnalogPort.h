#ifndef EV3LIB_PORTS_ANALOG_PORT_H_
#define EV3LIB_PORTS_ANALOG_PORT_H_

#include <cstddef>
#include <memory>
#include <utils/utilities.h>
#include <hardware/ports/SensorType.h>

namespace ev3lib::hardware::ports {

	struct AnalogPort: public destructible {
	    /**
	     * return the voltage present on pin 6 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual int getPin6() const = 0;

	    /**
	     * return the voltage present on pin 1 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual int getPin1() const = 0;

	    /**
	     * sets the sensor type.
	     * @return success status
	     */
        [[nodiscard]]
		virtual bool setType(SensorType mode) = 0;
	};

}


#endif /* EV3LIB_PORTS_ANALOG_PORT_H_ */

