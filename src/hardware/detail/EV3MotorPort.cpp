/*
 * Ev3MotorPort.cpp
 */

#include <stdexcept>

#include "EV3MotorPort.h"
#include <exceptions/EV3HardwareExceptions.h>

using namespace std;

namespace ev3lib {
namespace hardware {
namespace detail {

	EV3MotorPort::EV3MotorPort(EV3DeviceManager* manager, size_t port)
		: m_manager(manager), m_port(port)
	{
		open();
	}

	EV3MotorPort::~EV3MotorPort() {
		close();
		m_manager->disconnect(m_port, PortType::Motor);
	}


	void EV3MotorPort::setPower(int power) {
		uint8_t command[3];
		command[0] = (unsigned char)OutputCommand::Power;
		command[1] = m_port;
		command[2] = power;
		m_manager->m_pwmDevice.sendCommand(command);
	}

	void EV3MotorPort::stop(bool flt) {
		uint8_t command[3];
		command[0] = (unsigned char)OutputCommand::Stop;
		command[1] = m_port;
		command[2] = flt ? 0 : 1;
		m_manager->m_pwmDevice.sendCommand(command);
	}

	/**
	 * returns tachometer count
	 */
	int EV3MotorPort::getTachoCount() const {
		return m_manager->m_encoderDevice.getSensorData()[m_port].tachoCnt;
	}

	/**
	 * resets the tachometer count to 0;
	 */
	void EV3MotorPort::resetTachoCount() {
		uint8_t command[2];
		command[0] = (unsigned char)OutputCommand::ClearCount;
		command[1] = m_port;
		m_manager->m_pwmDevice.sendCommand(command);
	}

	/**
	 * Starts and stops the motor
	 */
	void EV3MotorPort::controlMotor(int power, MotorCommand command) {
		// Convert lejos power and mode to EV3 power and mode
		if (command >= MotorCommand::Stop)
		{
			stop(command == MotorCommand::Float);
		}
		else
		{
			if (command == MotorCommand::Backward)
				power = -power;
			setPower(power);
		}
	}

	bool EV3MotorPort::open() {
		try {
			uint8_t command[2];
			command[0] = (unsigned char)OutputCommand::Connect;
			command[1] = m_port;
			m_manager->m_pwmDevice.sendCommand(command);
		} catch (const io_error& e) {
			//Bug in the driver. Always throws the exception
		}
		return true;
	}

	void EV3MotorPort::close() {
		try {
			uint8_t command[2];
			command[0] = (unsigned char)OutputCommand::Disconnect;
			command[1] = m_port;
			m_manager->m_pwmDevice.sendCommand(command);
		} catch (const io_error& e) {
			//Bug in the driver. Always throws the exception
		}
	}


} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
