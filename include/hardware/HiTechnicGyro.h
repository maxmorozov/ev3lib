/*
 * HiTechnicGyro.h
 *
 *  Created on: 23 февр. 2015 г.
 *      Author: Max
 */

#ifndef EV3LIB_HITECHNICGYRO_H_
#define EV3LIB_HITECHNICGYRO_H_

namespace ev3lib {
namespace hardware {

class HiTechnicGyro {
private:
	detail::AnalogPort* m_port;
    float m_zero;

public:
	HiTechnicGyro(detail::AnalogPort* port);
	virtual ~HiTechnicGyro();

	float getData() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_HITECHNICGYRO_H_ */
