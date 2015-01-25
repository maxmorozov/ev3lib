/*
 * MotorManager.h
 *
 *  Created on: 18 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3LIB_MOTORMANAGER_H_
#define EV3LIB_MOTORMANAGER_H_

#include <hardware/detail/utilities.h>
#include <hardware/Tachometer.h>

namespace ev3lib {
namespace hardware {
namespace detail {

	enum class PWMMode : int {
		Float = 0, //Motor is not driven during off phase of PWM
		Brake = 1  //Motor is driven during off phase of PWM
	};

	enum class MotorCommand : int {
		Forward = 1,  // Motor is running forward
		Backward = 2, // Motor is running backwards
		Stop = 3,     // Motor is stopped (PWM drive still applied)
		Float = 4     // Motor is floating (no PWM drive)
	};

	struct MotorPort : public Tachometer {
	    /** Maximum power setting = 100% */
	    static const int MAX_POWER = 100;

	    /**
	     * Starts and stops the motor
	     */
		virtual void controlMotor(int power, MotorCommand command) = 0;
	};


	/**
	 * Manages EV3 motor port connections
	 */
	struct MotorManager: public destructible {
		/**
		 * Returns internal motor port structure. The clients should not delete it
		 */
		virtual MotorPort* getMotorPort(size_t port) = 0;
	};

}}}



#endif /* MOTORMANAGER_H_ */
