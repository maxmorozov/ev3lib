/*
 * motor_data.h
 */

#ifndef MOTOR_DATA_H_
#define MOTOR_DATA_H_

#include <hardware/detail/lms2012/ev3_types.h>

namespace ev3lib::hardware::detail::lejos {

typedef struct
{
	lms2012::SLONG baseCnt;
	lms2012::SLONG curCnt;
	lms2012::SLONG curVelocity;
	lms2012::SLONG tachoCnt;
	lms2012::SLONG state;
	lms2012::SLONG time;
	lms2012::SLONG time2;
	lms2012::SLONG serial;
} MOTORSHARED;

}

#endif /* MOTOR_DATA_H_ */
