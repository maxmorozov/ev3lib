/*
 * Ev3MotorPort.cpp
 *
 *  Created on: 18 џэт. 2015 у.
 *      Author: Max
 */

#include <stdexcept>

#include "EV3MotorPort.h"
#include "EV3SensorConstants.h"
#include <exceptions/EV3HardwareExceptions.h>

using namespace std;

namespace ev3lib {
namespace hardware {
namespace detail {

	namespace {
		typedef BufferCommand<unsigned char, 3> Command3;
		typedef BufferCommand<unsigned char, 2> Command2;
	}


	EV3MotorPort::EV3MotorPort(EV3DeviceManager* manager, size_t port)
		: m_manager(manager), m_port(port)
	{
		open();
	}

	EV3MotorPort::~EV3MotorPort() {
		close();
	}


	void EV3MotorPort::setPower(int power) {
		Command3 command;
		command[0] = (unsigned char)OutputCommand::Power;
		command[1] = m_port;
		command[2] = power;
		m_manager->m_pwmDevice.sendCommand(command);
	}

	void EV3MotorPort::stop(bool flt) {
		Command3 command;
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
		Command2 command;
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
			power = 0;
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
		m_manager->setPortMode(m_port, AnalogMode::Connected);

		try {
			Command2 command;
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
			Command2 command;
			command[0] = (unsigned char)OutputCommand::Disconnect;
			command[1] = m_port;
			m_manager->m_pwmDevice.sendCommand(command);
		} catch (const io_error& e) {
			//Bug in the driver. Always throws the exception
		}

		m_manager->setPortMode(m_port, AnalogMode::Disconnected);
	}


} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
