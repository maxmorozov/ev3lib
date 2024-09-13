/*
 * ev3_brick.h
 */

#pragma once

#include <hardware/detail/SensorsManager.h>
#include <hardware/detail/MotorManager.h>
#include <hardware/detail/UIManager.h>
#include <hardware/detail/Power.h>
#include <utils/utilities.h>
#include <memory>

namespace ev3lib::hardware::detail {

    class EV3Brick: public utils::destructible, utils::noncopyable {
		class EV3BrickImpl;
	private:
		std::unique_ptr<EV3BrickImpl> m_pimpl;
	public:
		EV3Brick();
    	//If we declare the destructor the default move constructor is not generated
    	EV3Brick(EV3Brick&&) = default;
		~EV3Brick() override;

		SensorsManager* getSensorsManager();
		const SensorsManager* getSensorsManager() const;

		MotorManager* getMotorManager();
		const MotorManager* getMotorManager() const;

		UIManager* getUIManager();
		const UIManager* getUIManager() const;

		Power* getBattery();
		const Power* getBattery() const;
	};

}
