/*
 * EV3UartSensor.cpp
 */
#include <utility>
#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/sensor/UartSensor.h>

namespace ev3lib::hardware::sensor {

    UartSensor::UartSensor(std::unique_ptr<port::UartPort> port, std::vector<ModeInfo> modes, size_t mode)
            : MultiModeSensor(std::move(modes), mode), m_port(std::move(port)) {
        if (!m_port->setMode(static_cast<port::MultiModePort::mode_type>(mode)))
            throw device_error("Unable to initialize device");
    }

    void UartSensor::switchMode(size_t newMode) {
        if (m_currentMode != newMode) {
            if (!m_port->setMode(static_cast<port::MultiModePort::mode_type>(newMode))) {
                throw boost::enable_error_info(std::invalid_argument("Invalid mode"))
                        << std_range_min(0)
                        << std_range_max(m_modes.size() - 1)
                        << std_range_index(newMode);
            }
        }
    }


    /**
     * Reset the sensor
     */
    void UartSensor::resetSensor() {
        m_port->resetSensor();
    }

}



