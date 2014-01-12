/*
 * IoException.h
 *
 *  Created on: 11 џэт. 2014 у.
 *      Author: Max
 */

#ifndef EV3LIB_HARDWARE_EXCEPTIONS_H_
#define EV3LIB_HARDWARE_EXCEPTIONS_H_

#include <stdexcept>
#include <boost/exception/all.hpp>

namespace ev3lib {

	typedef boost::error_info<struct errinfo_file_operation_flags_, int> errinfo_file_operation_flags;

	class io_error: public std::runtime_error, public boost::exception
	{
	public:
		io_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};

/*
	class io_error: public std::runtime_error {
	private:
		int m_errno;
	public:
		io_error(const std::string& message, int errno)
			: std::runtime_error(message), m_errno(errno)
		{
		}

		int code() const { return m_errno; }
	};

	inline int check(int result, const char* message) {
		if (result < 0) {
			throw io_error(message, errno);
		}
		return result;
	}
*/

}

#endif /* EV3LIB_HARDWARE_EXCEPTIONS_H_ */
