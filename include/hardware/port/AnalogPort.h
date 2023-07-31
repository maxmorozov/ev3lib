#pragma once

#include <cstddef>
#include <memory>
#include <utils/utilities.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::port {

    struct AnalogPort: public utils::destructible {
	    /**
	     * return the voltage present on pin 6 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual short getPin6() const = 0;

	    /**
	     * return the voltage present on pin 1 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual short getPin1() const = 0;

	    /**
	     * sets the sensor type.
	     * @return success status
	     */
        [[nodiscard]]
		virtual bool setType(SensorType mode) = 0;
	};

}
