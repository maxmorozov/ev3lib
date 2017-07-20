/*
 * motor.cpp
 */
#include <hardware/UnregulatedMotor.h>

namespace ev3lib {
namespace hardware {

using namespace detail;

UnregulatedMotor::UnregulatedMotor(detail::MotorPort* port)
	: m_port(port), m_power(0), m_currentState(MotorCommand::Float)
{

}

/**
 * Sets the motor state according the object's state
 */
void UnregulatedMotor::updateState() {
	m_port->controlMotor(m_power, m_currentState);
}

/**
 * Sets the output power in percents
 */
void UnregulatedMotor::setPower(unsigned int power)
{
	m_power = power;
	updateState();
}

/**
 * Rotate the motor in the forward direction
 */
void UnregulatedMotor::forward()
{
	m_currentState = MotorCommand::Forward;
	updateState();
}

/**
 * Rotate the motor in the backward direction
 */
void UnregulatedMotor::backward()
{
	m_currentState = MotorCommand::Backward;
	updateState();
}

/**
 * Stops rotation and leaves the circuit closed to brake the motor
 */
void UnregulatedMotor::stop()
{
	m_currentState = MotorCommand::Stop;
	updateState();
}

/**
 * Stops rotation and leaves the circuit opened. This lets the motor to rotate freely.
 */
void UnregulatedMotor::flt()
{
	m_currentState = MotorCommand::Float;
	updateState();
}

/**
 * returns tachometer count
 */
int UnregulatedMotor::getTachoCount() const
{
	return m_port->getTachoCount();
}

/**
 * resets the tachometer count to 0;
 */
void UnregulatedMotor::resetTachoCount()
{
	m_port->resetTachoCount();
}


}}


