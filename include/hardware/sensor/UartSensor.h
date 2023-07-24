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
		std::unique_ptr<port::UartPort> m_port;

		void switchMode(size_t newMode) override;
	public:
		UartSensor(std::unique_ptr<port::UartPort> port, std::vector<ModeInfo> modes, size_t mode = 0);

		/**
		 * Reset the sensor
		 */
		void resetSensor();
	};


}

