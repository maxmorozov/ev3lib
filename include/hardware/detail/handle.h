/*
 * handle.h
 */

#ifndef EV3LIB_HANDLE_H_
#define EV3LIB_HANDLE_H_

#include <cstddef>
#include <sys/types.h>
#include <utils/utilities.h>
#include <gsl/span>

namespace ev3lib {
namespace hardware {
namespace detail {
	/*
	 *	This class keeps Linux file handle of some character device.
	 *	Releases it in destructor.
	 *	Implements I/O operations.
	 */
	class handle final: noncopyable {
	private:
		int m_file;

	public:
		explicit handle(int handle) : m_file(handle) {}
		handle(const char* deviceName, int flags);
		handle(handle&& other) noexcept;
		~handle();

		handle& operator=(handle&& other) noexcept {
			std::swap(m_file, other.m_file);
		}

		explicit operator int() const {
			return m_file;
		}

		//Write bytes to the device
		ssize_t write(gsl::span<const uint8_t> data);

		//Send a control code to the device
		ssize_t ioctl(unsigned long command, const void* data);

		//Maps sensors data into user-mode memory.
		void* mmap(size_t size);
		// Deallocate any mapping for the region starting at ADDR and extending LEN bytes.
		//Returns 0 if successful, -1 for errors (and sets errno).
		int munmap(void* address, size_t size);
	};
}}}




#endif /* EV3LIB_HANDLE_H_ */
