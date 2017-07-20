/*
 * ev3_brick.h
 */

#ifndef EV3LIB_EV3_BRICK_H_
#define EV3LIB_EV3_BRICK_H_

#include <hardware/detail/SensorsManager.h>
#include <hardware/detail/MotorManager.h>
#include <hardware/detail/UIManager.h>
#include <hardware/detail/Power.h>
#include <utilities.h>
#include <memory>

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3Brick: public destructible, noncopyable {
		class EV3BrickImpl;
	private:
		std::unique_ptr<EV3BrickImpl> m_pimpl;
	public:
		EV3Brick();
		~EV3Brick();

		SensorsManager* getSensorsManager();
		const SensorsManager* getSensorsManager() const;

		MotorManager* getMotorManager();
		const MotorManager* getMotorManager() const;

		UIManager* getUIManager();
		const UIManager* getUIManager() const;

		Power* getBattery();
		const Power* getBattery() const;
	};

}}}



#endif /* EV3LIB_EV3_BRICK_H_ */
