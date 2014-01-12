/*
 * EV3SensorsManager.h
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3SENSORSMANAGER_H_
#define EV3SENSORSMANAGER_H_


#include <hardware/detail/device_traits.h>
#include <hardware/detail/ev3_device.h>
#include <hardware/detail/SensorsManager.h>

namespace ev3lib {
namespace hardware {
namespace detail {

struct DeviceInfo {
	ConnectionType connectionType = ConnectionType::None;
};

class EV3SensorsManager: public SensorsManager {
private:
	EV3Device<device_type::dcm> m_dcmDevice;
	EV3InputDevice<device_type::analog_sensor> m_analogDevice;
	EV3InputDevice<device_type::uart_sensor> m_uartDevice;
	EV3InputDevice<device_type::i2c_sensor> m_i2cDevice;

	DeviceInfo inputs[INPUTS];
	DeviceInfo outputs[OUTPUTS];

	void setDeviceType(DeviceInfo& deviceInfo, SensorType type, int mode);

public:
	EV3SensorsManager();

	virtual SensorType getSensorType(size_t port) override;
};

}}}

#endif /* EV3SENSORSMANAGER_H_ */
