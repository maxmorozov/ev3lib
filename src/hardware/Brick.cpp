/*
 * Brick.cpp
 */

#include <hardware/Brick.h>

namespace ev3lib::hardware {

Button Brick::getButton(Buttons id) {
	return Button(m_brick.getUIManager(), (size_t)id);
}

UnregulatedMotor Brick::getMotor(Motors id) {
	return UnregulatedMotor(m_brick.getMotorManager()->getMotorPort((size_t)id));
}

sensor::HiTechnicGyro Brick::getGyro(Sensors id) {
	return sensor::HiTechnicGyro(m_brick.getSensorsManager()->getAnalogPort((size_t)id));

}

sensor::AnalogSensor Brick::getAnalog(Sensors id) {
	return sensor::AnalogSensor(m_brick.getSensorsManager()->getAnalogPort((size_t)id));

}

sensor::NXTLightSensor Brick::getNxtLight(Sensors id) {
	return sensor::NXTLightSensor(m_brick.getSensorsManager()->getAnalogPort((size_t)id));
}

Battery Brick::getBattery() {
	return Battery(m_brick.getBattery());
}

sensor::ImuLsm6ds3 Brick::getImu(Sensors id) {
	return sensor::ImuLsm6ds3(m_brick.getSensorsManager()->getUartPort((size_t)id));

}


} /* namespace ev3lib */
