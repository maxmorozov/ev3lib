/*
 * EV3SensorConstants.h
 *
 *  Created on: 17 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3SENSORCONSTANTS_H_
#define EV3SENSORCONSTANTS_H_

namespace ev3lib {
namespace hardware {
namespace detail {

	class EV3SensorConstants {
	public:
		static const int PORTS = 4;
		static const int MOTORS = 4;

		static constexpr float ADC_REF_F = 5.0f; //5 V
	    /** MAX value returned as a RAW sensor reading for standard NXT A/D sensors */
	    static const int NXT_ADC_RES = 1023;

	};

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */




#endif /* EV3SENSORCONSTANTS_H_ */
