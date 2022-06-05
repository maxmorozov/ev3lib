/*
 * Ev3MotorPort.h
 */

#ifndef EV3MOTORPORT_H_
#define EV3MOTORPORT_H_

#include <hardware/detail/ev3_device.h>
#include "EV3DeviceManager.h"

namespace ev3lib::hardware::detail {

	class EV3MotorPort : public MotorPort {
	private:
		EV3DeviceManager* m_manager;
		size_t m_port;

		enum class OutputCommand : unsigned char {
			Connect = 1,
			Disconnect = 2,
			Start = 4,
			Stop = 5,
			SetType = 6,
			ClearCount = 7,
			Power = 8
		};

		bool open();
		void close();

	public:
		EV3MotorPort(EV3DeviceManager* manager, size_t port);
		~EV3MotorPort() override;

		/**
		 * returns tachometer count
		 */
		int getTachoCount() const override;

		/**
		 * resets the tachometer count to 0;
		 */
		void resetTachoCount() override;

		/**
		 * Starts and stops the motor
		 */
		void controlMotor(int power, MotorCommand command) override;

		void setPower(int power);

		void stop(bool flt);
	};

} /* namespace ev3lib::hardware::detail */

#endif /* EV3MOTORPORT_H_ */
