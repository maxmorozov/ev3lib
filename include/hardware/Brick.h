/*
 * Brick.h
 */

#pragma once

#include <hardware/detail/ev3_brick.h>
#include <hardware/Button.h>
#include <hardware/motor/UnregulatedMotor.h>
#include <hardware/sensor/HiTechnicGyro.h>
#include <hardware/sensor/AnalogSensor.h>
#include <hardware/sensor/NXTLightSensor.h>
#include <hardware/sensor/ImuLsm6ds3.h>
#include <hardware/sensor/CurrentSensorINA226.h>
#include <hardware/Battery.h>

namespace ev3lib::hardware {

	enum class Buttons : uint8_t {
		Up = 0,
		Enter = 1,
		Down = 2,
		Right = 3,
		Left = 4,
		Escape = 5
	};

	enum class Motors: uint8_t {
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};

	enum class Sensors: uint8_t {
		S1 = 0,
		S2 = 1,
		S3 = 2,
		S4 = 3
	};

class Brick {
private:
	detail::EV3Brick m_brick;

public:
	Brick() = default;

	Button getButton(Buttons id);

    motor::UnregulatedMotor getMotor(Motors id);

	sensor::HiTechnicGyro getGyro(Sensors id);

    sensor::AnalogSensor getAnalog(Sensors id);

    sensor::NXTLightSensor getNxtLight(Sensors id);

    sensor::ImuLsm6ds3 getImu(Sensors id);

    sensor::CurrentSensorINA226 getCurrentSensor(Sensors id);

	Battery getBattery();

};

} /* namespace ev3lib::hardware */
