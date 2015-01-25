/*
 * ev3_brick.cpp
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#include <hardware/detail/ev3_brick.h>
#include "EV3DeviceManager.h"

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3Brick::EV3BrickImpl {
	private:
		EV3DeviceManager m_manager;

	public:
		SensorsManager* getSensorsManager() { return &m_manager; }
		const SensorsManager* getSensorsManager() const { return &m_manager; }

		MotorManager* getMotorManager() { return &m_manager; }
		const MotorManager* getMotorManager() const { return &m_manager; }

		UIManager* getUIManager() { return &m_manager; }
		const UIManager* getUIManager() const { return &m_manager; }
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


}}}



