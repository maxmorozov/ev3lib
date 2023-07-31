/*
 * Brick.cpp
 */

#include <hardware/Brick.h>
#include <utils/type_utils.h>

namespace ev3lib::hardware {

Button Brick::getButton(Buttons id) {
	return Button(m_brick.getUIManager(), utils::to_underlying(id));
}

motor::UnregulatedMotor Brick::getMotor(Motors id) {
	return motor::UnregulatedMotor(m_brick.getMotorManager()->getMotorPort(utils::to_underlying(id)));
}

sensor::HiTechnicGyro Brick::getGyro(Sensors id) {
	return sensor::HiTechnicGyro(m_brick.getSensorsManager()->getAnalogPort(utils::to_underlying(id)));

}

sensor::AnalogSensor Brick::getAnalog(Sensors id) {
	return sensor::AnalogSensor(m_brick.getSensorsManager()->getAnalogPort(utils::to_underlying(id)));

}

sensor::NXTLightSensor Brick::getNxtLight(Sensors id) {
	return sensor::NXTLightSensor(m_brick.getSensorsManager()->getAnalogPort(utils::to_underlying(id)));
}

Battery Brick::getBattery() {
	return Battery(m_brick.getBattery());
}

sensor::ImuLsm6ds3 Brick::getImu(Sensors id) {
	return sensor::ImuLsm6ds3(m_brick.getSensorsManager()->getUartPort(utils::to_underlying(id)));

}

sensor::CurrentSensorINA226 Brick::getCurrentSensor(Sensors id) {
    return sensor::CurrentSensorINA226(m_brick.getSensorsManager()->getI2CPort(utils::to_underlying(id)));
}


} /* namespace ev3lib */
