/*
 * ev3_brick.cpp
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#include <hardware/detail/ev3_brick.h>
#include "EV3SensorsManager.h"

namespace ev3lib {
namespace hardware {
namespace detail {

EV3Brick::EV3Brick()
	: m_manager(new EV3SensorsManager())
{
}



}}}



