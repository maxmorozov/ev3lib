#pragma once

#include <memory>
#include <hardware/detail/SensorsManager.h>
#include <hardware/sensor/MultiModeSensor.h>

namespace ev3lib::hardware::sensor {

    /**
     * Base class for concrete sensor adapters
     */
	class UartSensor : public MultiModeSensor {
	protected:
		std::unique_ptr<ports::UartPort> m_port;

		void switchMode(size_t newMode);
	public:
		UartSensor(std::unique_ptr<ports::UartPort> port, std::vector<ModeInfo> modes, size_t mode = 0);

		/**
		 * Reset the sensor
		 */
		void resetSensor();
	};


}

