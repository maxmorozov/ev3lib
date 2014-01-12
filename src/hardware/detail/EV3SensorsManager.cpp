/*
 * EV3SensorsManager.cpp
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#include <hardware/detail/lms2012/lms2012.h>
#include "EV3SensorsManager.h"
#include <stdio.h>

namespace ev3lib {
namespace hardware {
namespace detail {

EV3SensorsManager::EV3SensorsManager()
{
}

SensorType EV3SensorsManager::getSensorType(size_t port)
{
	DATA8* inConn = m_analogDevice.getSensorData()->InConn;
	DATA8* inDcm  = m_analogDevice.getSensorData()->InDcm;
	printf("%03d %03d | %03d %03d | %03d %03d | %03d %03d\n", inConn[0], inDcm[0], inConn[1], inDcm[1], inConn[2], inDcm[2], inConn[3], inDcm[3]);

	//ConnectionType connection = (ConnectionType)m_analogDevice.getSensorData()->InConn[port];
	SensorType sensorType = (SensorType)m_analogDevice.getSensorData()->InDcm[port];
	return sensorType;
/*
	for (int i = 0; i < INPUTS; ++i) {
		if (inputs[i].connectionType != m_analogDevice.getSensorData()->InConn[i]) {
			// Connection type has changed
			inputs[i].connectionType = m_analogDevice.getSensorData()->InConn[i];
			setDeviceType(inputs[i], (SensorType)m_analogDevice.getSensorData()->InDcm[i], 0);

		}

	}
*/

}

void EV3SensorsManager::setDeviceType(DeviceInfo& deviceInfo, SensorType type, int mode)
{
/*
	if (deviceInfo.connectionType == ConnectionType::None) {
		type = SensorType::None;
	}
*/

}

}}}
