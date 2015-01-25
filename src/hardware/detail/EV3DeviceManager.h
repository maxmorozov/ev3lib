/*
 * EV3DeviceManager.h
 *
 *  Created on: 24 џэт. 2015 у.
 *      Author: Max
 */

#ifndef EV3DEVICEMANAGER_H_
#define EV3DEVICEMANAGER_H_

#include <memory>
#include <hardware/detail/device_traits.h>
#include <hardware/detail/ev3_device.h>
#include <hardware/detail/SensorsManager.h>
#include <hardware/detail/MotorManager.h>
#include <hardware/detail/UIManager.h>
#include "EV3SensorConstants.h"

namespace ev3lib {
namespace hardware {
namespace detail {

struct DeviceInfo {
	ConnectionType connectionType = ConnectionType::None;
};

class EV3DeviceManager: public SensorsManager, public MotorManager, public UIManager {
	friend class EV3MotorPort;
private:
	EV3Device<device_type::dcm> m_dcmDevice;

	EV3InputDevice<device_type::analog_sensor> m_analogDevice;
	EV3InputDevice<device_type::uart_sensor> m_uartDevice;
	EV3Device<device_type::i2c_sensor> m_i2cDevice;

	EV3InputDevice<device_type::motor_encoder> m_encoderDevice;
	EV3Device<device_type::pwm_motor> m_pwmDevice;

	EV3InputDevice<device_type::ui> m_buttonsDevice;

	std::unique_ptr<MotorPort> m_ports[EV3SensorConstants::MOTORS];

	DeviceInfo inputs[INPUTS];
	DeviceInfo outputs[OUTPUTS];

	void setDeviceType(DeviceInfo& deviceInfo, SensorType type, int mode);

public:
	EV3DeviceManager();

	virtual SensorType getSensorType(size_t port) const override;
	virtual ConnectionType getConnectionType(size_t port) const override;

	void setPortMode(size_t port, AnalogMode mode);

	/**
	 * Returns internal motor port structure. The clients should not delete it
	 */
	virtual MotorPort* getMotorPort(size_t port) override;

	/**
	 * Checks if the button is down
	 */
	virtual bool checkButton(size_t buttonNo) const override;

};

}}}

#endif /* EV3DEVICEMANAGER_H_ */
