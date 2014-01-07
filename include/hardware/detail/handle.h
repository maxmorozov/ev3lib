/*
 * handle.h
 *
 *  Created on: 07 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_HANDLE_H_
#define EV3LIB_HANDLE_H_

namespace ev3lib {
namespace hardware {
namespace detail {
	/*
	 *	This class keeps Linux file handle of some character device.
	 *	Releases it in destructor.
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

		//Don't allow creating copies
		handle(const handle& other) = delete;
		handle& operator=(const handle& other) = delete;
	};
}}}




#endif /* EV3LIB_HANDLE_H_ */
