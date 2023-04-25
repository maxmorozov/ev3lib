/*
 * handle.h
 */

#pragma once

#include <cstddef>
#include <sys/types.h>
#include <utils/utilities.h>
#include <span>
#include <cstdint>

namespace ev3lib::hardware::detail {
    /*
     *	This class keeps Linux file handle of some character device.
     *	Releases it in destructor.
     *	Implements I/O operations.
     */
    class handle final : utils::noncopyable {
    private:
        int m_file;

    public:
        explicit handle(int handle) : m_file(handle) {}

        handle(const char* deviceName, int flags);

        handle(handle&& other) noexcept;

        ~handle();

        handle& operator=(handle&& other) noexcept {
            std::swap(m_file, other.m_file);
            return *this;
        }

        explicit operator int() const {
            return m_file;
        }

        //Write bytes to the device
        ssize_t write(std::span<const uint8_t> data);

        //Send a control code to the device
        ssize_t ioctl(unsigned long command, const void* data);

        //Maps sensors data into user-mode memory.
        volatile void* mmap(size_t size);

        // Deallocate any mapping for the region starting at ADDR and extending LEN bytes.
        //Returns 0 if successful, -1 for errors (and sets errno).
        static int munmap(volatile void* address, size_t size);
    };
}
