/*
 * IoException.h
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

	class already_open_error: public std::runtime_error, public boost::exception
	{
	public:
		already_open_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};

	class device_error: public std::runtime_error, public boost::exception
	{
	public:
		device_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};


	namespace {
		typedef boost::error_info<struct tag_std_range_min,size_t> std_range_min;
		typedef boost::error_info<struct tag_std_range_max,size_t> std_range_max;
		typedef boost::error_info<struct tag_std_range_index,size_t> std_range_index;
	}

}

#endif /* EV3LIB_HARDWARE_EXCEPTIONS_H_ */
