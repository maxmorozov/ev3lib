#include <fcntl.h>
#include  <unistd.h>
#include  <sys/mman.h>
#include <stdio.h>

#include <hardware/detail/handle.h>

namespace ev3lib {
namespace hardware {
namespace detail {

handle::handle(const char* deviceName, int flags)
{
	printf("Opening device: %s\n", deviceName);
	m_file = ::open(deviceName, flags);
	printf("Device opened: %d\n", m_file);
}

handle::handle(handle&& other)
	: m_file(other.m_file)
{
	other.m_file = 0;
}

handle::~handle()
{
	if (m_file > 0)
		close(m_file);
}

ssize_t handle::write(const void* data, size_t size)
{
	return ::write(m_file, data, size);
}

void* handle::mmap(size_t size)
{
	printf("Mapping device memory. handle: %d\n", m_file);
	void* p = ::mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, m_file, 0);
	printf("Mapping device memory. address: %p\n", p);

	return p;
}

int handle::munmap(void* address, size_t size) {
	printf("Unmapping device memory. handle: %d, mapped addredd = %p\n", m_file, address);
	return ::munmap(address, size);
}

}}}
