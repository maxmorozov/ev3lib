/*
 * Brick.h
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3LIB_BRICK_H_
#define EV3LIB_BRICK_H_

#include <hardware/detail/ev3_brick.h>
#include <hardware/Button.h>
#include <hardware/UnregulatedMotor.h>
#include <hardware/HiTechnicGyro.h>
#include <hardware/Battery.h>

namespace ev3lib {
namespace hardware {

	enum class Buttons : int {
		Up = 0,
		Enter = 1,
		Down = 2,
		Right = 3,
		Left = 4,
		Escape = 5
	};

	enum class Motors: int {
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};

	enum class Sensors: int {
		S1 = 0,
		S2 = 1,
		S3 = 2,
		S4 = 3
	};

class Brick {
private:
	detail::EV3Brick m_brick;

public:
	Brick();

	Button getButton(Buttons id);

	UnregulatedMotor getMotor(Motors id);

	HiTechnicGyro getGyro(Sensors id);

	Battery getBattery();

};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_BRICK_H_ */
