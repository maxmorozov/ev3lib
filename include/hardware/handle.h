/*
 * handle.h
 *
 *  Created on: 07 ���. 2014 �.
 *      Author: Max
 */

#ifndef EV3LIB_HANDLE_H_
#define EV3LIB_HANDLE_H_

namespace ev3lib {
	namespace hardware {
		/*
		 *	This class keeps Linux file handle of some character device.
		 *	Closes it in destructor.
		 */
		class handle final {
		private:
			int m_file;
		public:
			explicit handle(int handle) : m_file(handle) {}
			handle(const char* deviceName, int flags);
			~handle();

			operator int() const {
				return m_file;
			}
		};
	}
}




#endif /* EV3LIB_HANDLE_H_ */
