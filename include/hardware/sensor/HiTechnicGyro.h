/*
 * HiTechnicGyro.h
 */

#pragma once

#include <memory>
#include <hardware/detail/SensorsManager.h>

namespace ev3lib::hardware::sensor {

class HiTechnicGyro: public utils::destructible {
private:
	std::unique_ptr<port::AnalogPort> m_port;
    float m_zero;

public:
	explicit HiTechnicGyro(std::unique_ptr<port::AnalogPort> port);

	float getData() const;
};


} /* namespace ev3lib::hardware::sensor */
