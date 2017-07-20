/*
 * EV3DeviceManager.cpp
 */

#include <boost/exception/all.hpp>
#include <stdexcept>
#include <algorithm>

#include <hardware/detail/lms2012/ev3_constants.h>
#include "exceptions/EV3HardwareExceptions.h"

#include "EV3MotorPort.h"
#include "EV3DeviceManager.h"
#include "EV3AnalogPort.h"
#include "EV3UartPort.h"


namespace ev3lib {
namespace hardware {
namespace detail {

namespace {
	typedef BufferCommand<unsigned char, 2> DCMCommand;
}

EV3DeviceManager::EV3DeviceManager() {
	std::fill_n(m_openPorts, count_of(m_openPorts), nullptr);
}

EV3DeviceManager::~EV3DeviceManager() {
	std::for_each(m_openPorts, m_openPorts + count_of(m_openPorts), [](DetachSubscriber* item) {if (item != nullptr) item->detach();});
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

void EV3DeviceManager::setPortMode(size_t port, PortType type, AnalogMode mode)
{
	DCMCommand command;
	int offset = type == PortType::Motor ? EV3SensorConstants::PORTS : 0;
	command[0] = (unsigned char)(port + offset);
	command[1] = (unsigned char)mode;
	m_dcmDevice.sendCommand(command);
}

void EV3DeviceManager::disconnect(size_t port, PortType type)
{
    if (type == PortType::Sensor) {
		m_openPorts[port] = nullptr;
	}
	setPortMode(port, type, AnalogMode::Disconnected);
}

void EV3DeviceManager::connectSensor(size_t port, DetachSubscriber* sensor) {
    if (port >= count_of(m_openPorts)) {
		throw boost::enable_error_info(std::range_error("Sensor port index is out of range")) <<
			std_range_min(0) <<
			std_range_max(EV3SensorConstants::PORTS - 1) <<
			std_range_index(port);
	}

    if (m_openPorts[port] == nullptr) {
    	setPortMode(port, PortType::Sensor, AnalogMode::Connected);
    	m_openPorts[port] = sensor;
		setPortMode(port, PortType::Sensor, AnalogMode::Float);
    }
    throw already_open_error("Port is already opened");
}

std::unique_ptr<AnalogPort> EV3DeviceManager::getAnalogPort(size_t port) {
   	auto sensor = std::make_unique<EV3AnalogPort>(this, port);
   	connectSensor(port, sensor.get());
	return sensor;
}

std::unique_ptr<UartPort> EV3DeviceManager::getUartPort(size_t port) {
	auto sensor = std::make_unique<EV3UartPort>(this, port);
   	connectSensor(port, sensor.get());
	return sensor;
}

/**
 * Returns internal motor port structure. The clients should not delete it
 */
MotorPort* EV3DeviceManager::getMotorPort(size_t port) {
	if (port < EV3SensorConstants::MOTORS) {
		if (!m_ports[port]) {
	    	setPortMode(port, PortType::Motor, AnalogMode::Connected);
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
	if (buttonNo < lms2012::BUTTONS) {
		return m_buttonsDevice.getSensorData()->Pressed[buttonNo] != 0;
	}
	throw boost::enable_error_info(std::range_error("Button index is out of range")) <<
		std_range_min(0) <<
		std_range_max(lms2012::BUTTONS - 1) <<
		std_range_index(buttonNo);
}

/**
 * Battery voltage
 */
short EV3DeviceManager::getBatteryVoltage() const {
	return m_analogDevice.getSensorData()->Cell123456;
}

/**
 * Current flowing from the battery
 */
short EV3DeviceManager::getMotorCurrent() const {
	return m_analogDevice.getSensorData()->MotorCurrent;
}

/**
 * Current flowing from the battery
 */
short EV3DeviceManager::getBatteryCurrent() const {
	return m_analogDevice.getSensorData()->BatteryCurrent;
}

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
