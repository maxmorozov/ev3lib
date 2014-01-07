#include <hardware/detail/handle.h>
#include <fcntl.h>
#include  <unistd.h>

namespace ev3lib {
namespace hardware {
namespace detail {

handle::handle(const char* deviceName, int flags)
{
	m_file = open(deviceName, flags);
}

handle::handle(handle&& other)
	: m_file(other.m_file)
{
	other.m_file = 0;
}

handle::~handle()
{
	if (m_file != 0)
		close(m_file);
}

}}}
