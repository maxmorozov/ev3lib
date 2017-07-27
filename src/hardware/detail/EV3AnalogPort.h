/*
 * EV3AnalogPort.h
 */

#ifndef EV3ANALOGPORT_H_
#define EV3ANALOGPORT_H_

#include <hardware/detail/ev3_device.h>
#include "EV3DeviceManager.h"
#include "DetachSubscriber.h"

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3AnalogPort: public AnalogPort, public DetachSubscriber {
	private:
		EV3DeviceManager* m_manager;
		size_t m_port;

		bool setPinMode(AnalogMode mode);

	public:
		EV3AnalogPort(EV3DeviceManager* manager, size_t port);

		~EV3AnalogPort() override;

	    /**
	     * return the voltage present on pin 6 of the sensor port
	     * @return raw ADC voltage reading
	     */
		int getPin6() const override;

	    /**
	     * return the voltage present on pin 1 of the sensor port
	     * @return raw ADC voltage reading
	     */
		int getPin1() const override;

	    /**
	     * sets the sensor type.
	     * @return success status
	     */
		bool setType(int mode) override;

		void detach() override;
	};

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3ANALOGPORT_H_ */
