/*
 * motor_data.h
 *
 *  Created on: 18 џэт. 2015 у.
 *      Author: Max
 */

#ifndef MOTOR_DATA_H_
#define MOTOR_DATA_H_

#include <hardware/detail/lms2012/lmstypes.h>

typedef struct
{
    SLONG baseCnt;
    SLONG curCnt;
    SLONG curVelocity;
    SLONG tachoCnt;
    SLONG state;
    SLONG time;
    SLONG time2;
    SLONG serial;
} MOTORSHARED;


#endif /* MOTOR_DATA_H_ */
