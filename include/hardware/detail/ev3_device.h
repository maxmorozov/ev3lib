/*
 * ev3_device.h
 */

#pragma once

#include <hardware/detail/handle.h>
#include <hardware/detail/device_traits.h>
#include <span>

namespace ev3lib::hardware::detail {

	/**
	 * Device that can be controlled using commands
	 */
	template <device_type type>
	class EV3Device {
	protected:
		//EV3 device singleton
		handle m_device;

	public:
		EV3Device();

		//Writes the command into the file.
		//Returns the number of written bytes or -1
		ssize_t sendCommand(std::span<uint8_t> command) {
			//TODO add error checking using exceptions
			return m_device.write(command);
		}

		//Writes the command into the file.
        //Returns the status. It depends on the command.
        //Usually 0 means success and -1 means failure
		ssize_t ioctl(unsigned long command, const void* data) {
			return m_device.ioctl(command, data);
		}
	};

	//Initialization
	template <device_type type>
	EV3Device<type>::EV3Device()
		: m_device(device_traits<type>::device_name, device_traits<type>::device_flags)
	{
	}


	/**
	 * Device that supports reading input values and provides memory mapped access to collected input data
	 */
	template <device_type type>
	class EV3InputDevice: public EV3Device<type>
	{
	public:
		using device_map_type = typename device_traits<type>::device_map_type;
		static constexpr size_t ports_count = device_traits<type>::ports_count;

	private:
		device_map_type* m_map;
	public:
		EV3InputDevice() {
			m_map = (device_map_type*)EV3Device<type>::m_device.mmap(device_traits<type>::sensor_data_size);
		}
		~EV3InputDevice() {
			EV3Device<type>::m_device.munmap(m_map, device_traits<type>::sensor_data_size);
		}

		//Returns array of structures that allow reading sensors values
		//The array size is equal to ports_count constant
		device_map_type* getSensorData() {	return m_map; }
		const device_map_type* getSensorData() const { return m_map; }
	};

}
