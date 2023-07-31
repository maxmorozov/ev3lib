#pragma once

#include <hardware/detail/lms2012/ev3_types.h>

namespace ev3lib::hardware::detail::lejos {


	static const int UART_PORT_ERROR    = 0x80;        //!< Sensor error

	// leJOS commands
	typedef   struct
	{
		lms2012::UBYTE     Port;
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

	static constexpr uint32_t UART_SET_CONFIG  =  _IOWR('u',4,UARTCONFIG);
	static constexpr uint32_t UART_RAW_READ    =  _IOWR('u',5,void *);
	static constexpr uint32_t UART_RAW_WRITE   =  _IOWR('u',6,void *);
	static constexpr uint32_t UART_CONNECT     =  _IOWR('u',7,DEVCTL);
	static constexpr uint32_t UART_DISCONNECT  =  _IOWR('u',8,DEVCTL);
	static constexpr uint32_t UART_SETMODE     =  _IOWR('u',9,DEVCTL);


	static constexpr lms2012::DATA8 UART_MODE_RAW   =  ((lms2012::DATA8) -1);

    //IIC extension
    static constexpr uint32_t IIC_CONNECT           = _IOWR('i',7,DEVCTL);
    static constexpr uint32_t IIC_DISCONNECT        = _IOWR('i',8,DEVCTL);
    static constexpr uint32_t IIC_IO                = _IOWR('i',9,DEVCTL);

    static constexpr int STATUS_OK = 0;
    static constexpr int STATUS_BUSY = 1;
    static constexpr int STATUS_FAIL = 2;
    static constexpr int STATUS_STOP = 4;

}
