/*
 * handle.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_HANDLE_H_
#define EV3LIB_HANDLE_H_

#include <stddef.h>
#include <sys/types.h>

namespace ev3lib {
namespace hardware {
namespace detail {
	/*
	 *	This class keeps Linux file handle of some character device.
	 *	Releases it in destructor.
	 *	Implements I/O operations.
	 */
	class handle final {
	private:
		int m_file;

	public:
		explicit handle(int handle) : m_file(handle) {}
		handle(const char* deviceName, int flags);
		handle(handle&& other);
		~handle();

		operator int() const {
			return m_file;
		}

		//Write command to device
		ssize_t write(const void* data, size_t size);

		//Maps sensors data into user-mode memory.
		//Returns 0 if successful, -1 for errors (and sets errno).
		void* mmap(size_t size);
		// Deallocate any mapping for the region starting at ADDR and extending LEN bytes.
		//Returns 0 if successful, -1 for errors (and sets errno).
		int munmap(void* address, size_t size);

		//Don't allow creating copies
		handle(const handle& other) = delete;
		handle& operator=(const handle& other) = delete;
	};
}}}




#endif /* EV3LIB_HANDLE_H_ */
