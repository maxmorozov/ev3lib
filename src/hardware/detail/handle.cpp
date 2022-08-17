#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <hardware/detail/handle.h>
#include <hardware/detail/lms2012/ev3_constants.h>
#include <exceptions/EV3HardwareExceptions.h>

namespace ev3lib::hardware::detail {

    handle::handle(const char* deviceName, int flags) {
        m_file = ::open(deviceName, flags);
        if (m_file < 0) {
            throw io_error("Device opening failure")
                    << boost::errinfo_file_name(deviceName)
                    << boost::errinfo_errno(errno)
                    << errinfo_file_operation_flags(flags);
        }
    }

    handle::handle(handle&& other) noexcept
            : m_file(other.m_file) {
        other.m_file = 0;
    }

    handle::~handle() {
        if (m_file >= lms2012::MIN_HANDLE)
            close(m_file);
    }

    ssize_t handle::write(gsl::span<const uint8_t> data) {
        ssize_t written = ::write(m_file, data.data(), utils::size(data));
        if (written < 0) {
            throw io_error("Write operation has failed") <<
                                                         boost::errinfo_errno(errno);
        }
        return written;
    }

    void* handle::mmap(size_t size) {
        void* p = ::mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, m_file, 0);
        if (p == MAP_FAILED) {
            throw io_error("Mapping device memory has failed") <<
                                                               boost::errinfo_errno(errno);
        }
        return p;
    }

    //Send a control code to the device
    ssize_t handle::ioctl(unsigned long command, const void* data) {
        ssize_t size = ::ioctl(m_file, command, data);
        if (size < 0) {
            throw io_error("IoCtl operation has failed") <<
                                                         boost::errinfo_errno(errno);
        }
        return size;
    }

    int handle::munmap(void* address, size_t size) {
        if (address != MAP_FAILED)
            return ::munmap(address, size);

        return -1;
    }

}
