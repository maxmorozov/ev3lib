#ifndef __EV3LIB_UNREGULATED_MOTOR_H
#define __EV3LIB_UNREGULATED_MOTOR_H

#include <hardware/detail/MotorManager.h>

namespace ev3lib {
	namespace hardware {

		class UnregulatedMotor : public Tachometer {
		private:
			detail::MotorPort* m_port;
			unsigned int m_power;
			detail::MotorCommand m_currentState;

			/**
			 * Sets the motor state according the object's state
			 */
			void updateState();

		public:
			UnregulatedMotor(detail::MotorPort* port);

			/**
			 * Sets the output power in percents
			 */
			void setPower(unsigned int power);

			/**
			 * Rotate the motor in the forward direction
			 */
			void forward();

			/**
			 * Rotate the motor in the backward direction
			 */
			void backward();

			/**
			 * Stops rotation and leaves the circuit closed to brake the motor
			 */
			void stop();

			/**
			 * Stops rotation and leaves the circuit opened. This lets the motor to rotate freely.
			 */
			void flt();

			/**
			 * returns tachometer count
			 */
			virtual int getTachoCount() const override;

			/**
			 * resets the tachometer count to 0;
			 */
			virtual void resetTachoCount() override;

		};
	}
}

#endif //__EV3LIB_UNREGULATED_MOTOR_H
