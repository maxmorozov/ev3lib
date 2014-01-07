#include <hardware/handle.h>
#include <fcntl.h>
#include  <unistd.h>

namespace ev3lib {
namespace hardware {

handle::handle(const char* deviceName, int flags)
{
	m_file = open(deviceName, flags);

}

handle::~handle()
{
	close(m_file);
}


}}
