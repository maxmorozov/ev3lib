/*
 * EV3UartPort.h
 */

#ifndef EV3LIB_EV3UARTPORT_H_
#define EV3LIB_EV3UARTPORT_H_

#include <memory>
#include <hardware/detail/SensorsManager.h>

#include "MultiModeSensor.h"

namespace ev3lib {
namespace hardware {

    /**
     * Base class for concrete sensor adapters
     */
	class UartSensor : public MultiModeSensor {
	protected:
		std::unique_ptr<detail::UartPort> m_port;

		void switchMode(size_t newMode);

	public:
		UartSensor(std::unique_ptr<detail::UartPort>&& port, std::vector<std::unique_ptr<SensorMode>>&& modes);
		UartSensor(std::unique_ptr<detail::UartPort>&& port, std::vector<std::unique_ptr<SensorMode>>&& modes, size_t mode);
		UartSensor(UartSensor&& other) noexcept ;

		/**
		 * Reset the sensor
		 */
		void reset();
	};


}}



#endif /* EV3LIB_EV3UARTPORT_H_ */
