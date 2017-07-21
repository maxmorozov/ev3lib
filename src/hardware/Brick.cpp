/*
 * Brick.cpp
 */

#include <hardware/Brick.h>

namespace ev3lib {
namespace hardware {

Brick::Brick() {
	// TODO Auto-generated constructor stub

}

Button Brick::getButton(Buttons id) {
	return Button(m_brick.getUIManager(), (size_t)id);
}

UnregulatedMotor Brick::getMotor(Motors id) {
	return UnregulatedMotor(m_brick.getMotorManager()->getMotorPort((size_t)id));
}

HiTechnicGyro Brick::getGyro(Sensors id) {
	return HiTechnicGyro(m_brick.getSensorsManager()->getAnalogPort((size_t)id));

}

AnalogSensor Brick::getAnalog(Sensors id) {
	return AnalogSensor(m_brick.getSensorsManager()->getAnalogPort((size_t)id));

}

NXTLightSensor Brick::getNxtLight(Sensors id) {
	return NXTLightSensor(m_brick.getSensorsManager()->getAnalogPort((size_t)id));
}

Battery Brick::getBattery() {
	return Battery(m_brick.getBattery());
}

ImuLsm6ds3 Brick::getImu(Sensors id) {
	return ImuLsm6ds3(m_brick.getSensorsManager()->getUartPort((size_t)id));

}


} /* namespace hardware */
} /* namespace ev3lib */
