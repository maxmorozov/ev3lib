/*
 * HiTechnicGyro.cpp
 */

#include <hardware/sensor/HiTechnicGyro.h>
#include "../detail/AnalogSensorHelpers.h"

namespace ev3lib {
namespace hardware {

HiTechnicGyro::HiTechnicGyro(std::unique_ptr<detail::AnalogPort> port)
	: m_port(std::move(port)), m_zero(614.0f)
{

}

float HiTechnicGyro::getData() const
{
	return detail::AnalogSensorHelpers::NXTRawValue(m_port->getPin1()) - m_zero;
}

} /* namespace hardware */
} /* namespace ev3lib */
