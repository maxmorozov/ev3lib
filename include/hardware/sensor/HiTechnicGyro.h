/*
 * HiTechnicGyro.h
 */

#ifndef EV3LIB_HITECHNICGYRO_H_
#define EV3LIB_HITECHNICGYRO_H_

#include <memory>
#include <hardware/detail/SensorsManager.h>

namespace ev3lib {
namespace hardware {

class HiTechnicGyro: public destructible {
private:
	std::unique_ptr<detail::AnalogPort> m_port;
    float m_zero;

public:
	explicit HiTechnicGyro(std::unique_ptr<detail::AnalogPort> port);

	float getData() const;
};


} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_HITECHNICGYRO_H_ */
