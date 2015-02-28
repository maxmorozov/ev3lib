/*
 * ev3_brick.cpp
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#include <hardware/detail/ev3_brick.h>
#include "EV3DeviceManager.h"
#include "EV3Battery.h"

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3Brick::EV3BrickImpl {
	private:
		EV3DeviceManager m_manager;
		EV3Battery m_battery;

	public:
		EV3BrickImpl()
			: m_battery(&m_manager)
		{
		}


		SensorsManager* getSensorsManager() { return &m_manager; }
		const SensorsManager* getSensorsManager() const { return &m_manager; }

		MotorManager* getMotorManager() { return &m_manager; }
		const MotorManager* getMotorManager() const { return &m_manager; }

		UIManager* getUIManager() { return &m_manager; }
		const UIManager* getUIManager() const { return &m_manager; }

		Power* getBattery() { return &m_battery; }
		const Power* getBattery() const { return &m_battery; }
	};

EV3Brick::EV3Brick()
	: m_pimpl(new EV3BrickImpl())
{
}

EV3Brick::~EV3Brick()
{

}

SensorsManager* EV3Brick::getSensorsManager() {
	return m_pimpl->getSensorsManager();
}
const SensorsManager* EV3Brick::getSensorsManager() const {
	return m_pimpl->getSensorsManager();
}

MotorManager* EV3Brick::getMotorManager() {
	return m_pimpl->getMotorManager();

}
const MotorManager* EV3Brick::getMotorManager() const {
	return m_pimpl->getMotorManager();

}

UIManager* EV3Brick::getUIManager() {
	return m_pimpl->getUIManager();
}
const UIManager* EV3Brick::getUIManager() const {
	return m_pimpl->getUIManager();
}

Power* EV3Brick::getBattery() {
	return m_pimpl->getBattery();
}
const Power* EV3Brick::getBattery() const {
	return m_pimpl->getBattery();
}


}}}



