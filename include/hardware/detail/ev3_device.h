/*
 * ev3_device.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_EV3_DEVICE_H_
#define EV3LIB_EV3_DEVICE_H_

#include <hardware/detail/handle.h>
#include <hardware/detail/device_traits.h>

namespace ev3lib {
namespace hardware {
namespace detail {

	template <device_type type>
	class EV3Device {
	protected:
		//EV3 device singleton
		static handle m_device;
	public:

	};

	//Initialization
	template <device_type type>
	handle EV3Device<type>::m_device(device_traits<type>::device_name, device_traits<type>::device_flags);

	//Options

	//By adding this option the device class gets ability to send command to the device
	template <device_type type>
	class SendCommandOption: private EV3Device<type> {
	public:
		//Writes the command into the file.
		//Returns the number of written bytes or -1
		template <typename CommandType>
		ssize_t sendCommand(const CommandType& command) {
			//TODO add error checking using exceptions
			return EV3Device<type>::m_device.write(command.buffer(), CommandType::size);
		}
	};

	//By adding this option the device class gets ability to read sensor data
	template <device_type type>
	class ReadSensorOption: private EV3Device<type> {
	public:
		typedef typename device_traits<type>::device_map_type device_map_type;
		static const size_t ports_count = device_traits<type>::ports_count;

	private:
		//Helper class to map and unmap sensor data structures into user-space memory
		class memory_mapper {
		private:
			device_map_type* m_map;
		public:
			memory_mapper() {
				m_map = (device_map_type*)EV3Device<type>::m_device.mmap(device_traits<type>::sensor_data_size);
			}

			~memory_mapper() {
				EV3Device<type>::m_device.munmap(m_map, device_traits<type>::sensor_data_size);
			}

			device_map_type* get() { return m_map; }
			const device_map_type* get() const { return m_map; }
		};

		static memory_mapper m_sensorData;

	public:
		//Returns array of structures that allow reading sensors values
		//The array size is equal to ports_count constant
		device_map_type* getSensorData() {	return m_sensorData.get();	}
		const device_map_type* getSensorData() const { return m_sensorData.get();	}
	};

	template<device_type type>
	typename ReadSensorOption<type>::memory_mapper ReadSensorOption<type>::m_sensorData;

	//
	template <device_type type>
	class EV3OutputDevice:
			public SendCommandOption<type> {

	};


	template <device_type type>
	class EV3InputDevice:
			public SendCommandOption<type>,
			public ReadSensorOption<type> {

	};

}}}



#endif /* EV3LIB_EV3_DEVICE_H_ */
