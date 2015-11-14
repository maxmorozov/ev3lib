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
	return std::move(HiTechnicGyro(std::move(m_brick.getSensorsManager()->getAnalogPort((int)id))));

}

AnalogSensor Brick::getAnalog(Sensors id) {
	return std::move(AnalogSensor(std::move(m_brick.getSensorsManager()->getAnalogPort((int)id))));

}

NXTLightSensor Brick::getNxtLight(Sensors id) {
	return std::move(NXTLightSensor(std::move(m_brick.getSensorsManager()->getAnalogPort((int)id))));
}

Battery Brick::getBattery() {
	return Battery(m_brick.getBattery());
}


} /* namespace hardware */
} /* namespace ev3lib */
