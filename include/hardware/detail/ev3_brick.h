/*
 * ev3_brick.h
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_EV3_BRICK_H_
#define EV3LIB_EV3_BRICK_H_

#include <hardware/detail/SensorsManager.h>
#include <hardware/detail/utilities.h>
#include <memory>

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3Brick: public destructible, noncopyable {
	private:
		std::unique_ptr<SensorsManager> m_manager;
	public:
		EV3Brick();

		SensorsManager* getSensorsManager() const {	return m_manager.get(); }
	};

}}}



#endif /* EV3LIB_EV3_BRICK_H_ */
