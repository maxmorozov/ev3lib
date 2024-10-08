/*
 * EV3AnalogPort.h
 */

#pragma once

#include "EV3DeviceManager.h"
#include "DetachSubscriber.h"

namespace ev3lib::hardware::detail {

	class EV3AnalogPort: public port::AnalogPort, public DetachSubscriber {
    public:
        using port_type = SensorsManager::port_type;

	private:
		EV3DeviceManager* m_manager;
        port_type m_port;

		bool setPinMode(AnalogMode mode);

        void close();
	public:
		EV3AnalogPort(EV3DeviceManager* manager, size_t port);

		~EV3AnalogPort() override;

	    /**
	     * return the voltage present on pin 6 of the sensor port
	     * @return raw ADC voltage reading
	     */
		short getPin6() const override;

	    /**
	     * return the voltage present on pin 1 of the sensor port
	     * @return raw ADC voltage reading
	     */
		short getPin1() const override;

	    /**
	     * sets the sensor type.
	     * @return success status
	     */
		bool setType(port::SensorType mode) override;

		void detach() override;
	};

} /* namespace ev3lib::hardware::detail */
