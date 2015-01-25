/*
 * EV3DeviceManager.cpp
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#include <boost/exception/all.hpp>
#include <stdexcept>

#include <hardware/detail/lms2012/lms2012.h>

#include "EV3MotorPort.h"
#include "EV3DeviceManager.h"


namespace ev3lib {
namespace hardware {
namespace detail {

namespace {
	typedef boost::error_info<struct tag_std_range_min,size_t> std_range_min;
	typedef boost::error_info<struct tag_std_range_max,size_t> std_range_max;
	typedef boost::error_info<struct tag_std_range_index,size_t> std_range_index;

	typedef BufferCommand<unsigned char, 2> DCMCommand;
}

EV3DeviceManager::EV3DeviceManager() {
}

SensorType EV3DeviceManager::getSensorType(size_t port) const
{
	return (SensorType)m_analogDevice.getSensorData()->InDcm[port];
}

ConnectionType EV3DeviceManager::getConnectionType(size_t port) const
{
	return (ConnectionType)m_analogDevice.getSensorData()->InConn[port];
}

void EV3DeviceManager::setDeviceType(DeviceInfo& deviceInfo, SensorType type, int mode)
{
/*
	if (deviceInfo.connectionType == ConnectionType::None) {
		type = SensorType::None;
	}
*/

}

void EV3DeviceManager::setPortMode(size_t port, AnalogMode mode)
{
	DCMCommand command;
	command[0] = (unsigned char)(port + EV3SensorConstants::PORTS);
	command[1] = (unsigned char)mode;
	m_dcmDevice.sendCommand(command);
}


/**
 * Returns internal motor port structure. The clients should not delete it
 */
MotorPort* EV3DeviceManager::getMotorPort(size_t port) {
	if (port < EV3SensorConstants::MOTORS) {
		if (!m_ports[port]) {
			m_ports[port].reset(new EV3MotorPort(this, port));
		}
		return m_ports[port].get();
	} else {
		throw boost::enable_error_info(std::range_error("Motor index is out of range")) <<
			std_range_min(0) <<
			std_range_max(EV3SensorConstants::MOTORS - 1) <<
			std_range_index(port);
	}
}

/**
 * Checks if the button is down
 */
bool EV3DeviceManager::checkButton(size_t buttonNo) const {
	if (buttonNo < BUTTONS) {
		return m_buttonsDevice.getSensorData()->Pressed[buttonNo] != 0;
	}
	throw boost::enable_error_info(std::range_error("Button index is out of range")) <<
		std_range_min(0) <<
		std_range_max(BUTTONS - 1) <<
		std_range_index(buttonNo);
}

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
