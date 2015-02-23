/*
 * Brick.cpp
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#include <hardware/Brick.h>

namespace ev3lib {
namespace hardware {

Brick::Brick() {
	// TODO Auto-generated constructor stub

}

Button Brick::getButton(Buttons id) {
	return Button(m_brick.getUIManager(), (int)id);
}

UnregulatedMotor Brick::getMotor(Motors id) {
	return UnregulatedMotor(m_brick.getMotorManager()->getMotorPort((int)id));
}

HiTechnicGyro Brick::getGyro(Sensors id) {
	return HiTechnicGyro(m_brick.getSensorsManager()()->getS((int)id)

}


} /* namespace hardware */
} /* namespace ev3lib */
