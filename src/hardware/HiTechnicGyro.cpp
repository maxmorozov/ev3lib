/*
 * HiTechnicGyro.cpp
 *
 *  Created on: 23 ����. 2015 �.
 *      Author: Max
 */

#include <hardware/HiTechnicGyro.h>
#include "detail/AnalogSensorHelpers.h"

namespace ev3lib {
namespace hardware {

HiTechnicGyro::HiTechnicGyro(detail::AnalogPort* port)
	: m_port(port), m_zero(614.0f)
{

}

HiTechnicGyro::~HiTechnicGyro()
{
}

float HiTechnicGyro::getData() const
{
	return detail::AnalogSensorHelpers::NXTRawValue(m_port->getPin1()) - m_zero;

}

} /* namespace hardware */
} /* namespace ev3lib */
