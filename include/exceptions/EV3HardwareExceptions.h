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
		explicit io_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};

	class already_open_error: public std::runtime_error, public boost::exception
	{
	public:
		explicit already_open_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};

	class device_error: public std::runtime_error, public boost::exception
	{
	public:
		explicit device_error(const std::string& message)
			: std::runtime_error(message)
		{
		}
	};

    class iic_error: public std::runtime_error, public boost::exception
    {
    public:
        explicit iic_error(const std::string& message)
                : std::runtime_error(message)
        {
        }
    };

	typedef boost::error_info<struct tag_std_range_min,size_t> std_range_min;
	typedef boost::error_info<struct tag_std_range_max,size_t> std_range_max;
	typedef boost::error_info<struct tag_std_range_index,size_t> std_range_index;

    typedef boost::error_info<struct tag_error_code,size_t> error_code;
}

#endif /* EV3LIB_HARDWARE_EXCEPTIONS_H_ */
