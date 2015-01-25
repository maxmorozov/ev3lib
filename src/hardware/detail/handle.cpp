#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include <hardware/detail/handle.h>
#include <hardware/detail/lms2012/lms2012.h>
#include<exceptions/EV3HardwareExceptions.h>

namespace ev3lib {
namespace hardware {
namespace detail {

handle::handle(const char* deviceName, int flags)
{
	//printf("Opening device: %s, flags: %d\n", deviceName, flags);
	m_file = ::open(deviceName, flags);
	if (m_file < 0) {
        throw io_error("Device opening failure") <<
                boost::errinfo_file_name(deviceName) <<
                boost::errinfo_errno(errno) <<
                errinfo_file_operation_flags(flags);
	}
	//printf("Device opened: %d\n", m_file);
}

handle::handle(handle&& other)
	: m_file(other.m_file)
{
	other.m_file = 0;
}

handle::~handle()
{
	if (m_file >= MIN_HANDLE)
		close(m_file);
}

ssize_t handle::write(const void* data, size_t size)
{
	//printf("Writing %d bytes to handle %d\n", size, m_file);
	//for (int i=0; i < (int)size; ++i)
	//	printf("data[%d]=%d\n", i, (int)((const char*)data)[i]);

	ssize_t written = ::write(m_file, data, size);
	//printf("Writing result %d, written size %d\n", errno, written);
	if (written < 0) {
        throw io_error("Write operation has failed") <<
                boost::errinfo_errno(errno);
	}
	return written;
}

void* handle::mmap(size_t size)
{
	//printf("Mapping device memory. handle: %d\n", m_file);

	void* p = ::mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, m_file, 0);
	if (p == MAP_FAILED) {
        throw io_error("Mapping device memory has failed") <<
                boost::errinfo_errno(errno);
	}

	//printf("Mapping device memory. address: %p\n", p);

	return p;
}

//Send a control code to the device
ssize_t handle::ioctl(unsigned long command, const void* data)
{
	return ::ioctl(m_file, command, data);
}

int handle::munmap(void* address, size_t size) {
	//printf("Unmapping device memory. handle: %d, mapped addredd = %p\n", m_file, address);
	if (address != MAP_FAILED)
		return ::munmap(address, size);
	else
		return -1;
}

}}}
