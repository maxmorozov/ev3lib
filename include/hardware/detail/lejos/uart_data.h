#ifndef LEJOS_UART_DATA_H
#define LEJOS_UART_DATA_H

#include <hardware/detail/lms2012/ev3_types.h>

namespace ev3lib {
namespace hardware {
namespace detail {

namespace lejos {


	static const int UART_PORT_ERROR    = 0x80;        //!< Sensor error

	// leJOS commands
	typedef   struct
	{
		lms2012::DATA8     Port;
		lms2012::DATA8     Cmd;
		lms2012::DATA8     Arg;
	}
	DEVCTL;

	/* leJOS additions for RAW UART access */
	typedef struct
	{
		lms2012::DATA32 Port;
		lms2012::DATA32 BitRate;
	}
	UARTCONFIG;

	static const int UART_SET_CONFIG  =  _IOWR('u',4,UARTCONFIG);
	static const int UART_RAW_READ    =  _IOWR('u',5,void *);
	static const int UART_RAW_WRITE   =  _IOWR('u',6,void *);
	static const int UART_CONNECT     =  _IOWR('u',7,DEVCTL);
	static const int UART_DISCONNECT  =  _IOWR('u',8,DEVCTL);
	static const int UART_SETMODE     =  _IOWR('u',9,DEVCTL);


	static const int UART_MODE_RAW    =  ((lms2012::DATA8) -1);

}}}}

#endif //LEJOS_UART_DATA_H
