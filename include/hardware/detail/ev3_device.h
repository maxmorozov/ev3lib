/*
 * ev3_device.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_EV3_DEVICE_H_
#define EV3LIB_EV3_DEVICE_H_

#include <unistd.h>
#include  <sys/mman.h>

#include <hardware/detail/handle.h>
#include <hardware/detail/device_traits.h>

namespace ev3lib {
namespace hardware {
namespace detail {

	template <handle_type type>
	class ev3device {
	private:
		typedef typename device_traits<type>::device_map_type device_map_type;

		//EV3 device singleton
		static const handle m_device;

		static handle create_device();
	public:

		//Writes the command into the file.
		//Returns the number of written bytes or -1
		template <typename CommandType>
		ssize_t send_command(const CommandType& command) {
			//TODO add error checking using exceptions
			return ::write(m_device, command.buffer(), CommandType::size);
		}

		device_map_type* mmap() {
			return (device_map_type*)::mmap(0, sizeof(device_map_type) * device_traits<type>::ports_count, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, m_device, 0);
		}

	};

	//Initialization
	template <handle_type type>
	const handle ev3device<type>::m_device = ev3device<type>::create_device();

}}}



#endif /* EV3LIB_EV3_DEVICE_H_ */
