/*
 * ev3_types.h
 */

#pragma once

#include <sys/ioctl.h>
#include <hardware/detail/lms2012/ev3_constants.h>

//#define   DISABLE_OLD_COLOR             //!< Don't support NXT color sensor
//#define   DISABLE_FAST_DATALOG_BUFFER
#define   UART1_FAKE_INTERRUPT          //!< Don't use real interrupt on UART1 (linux prompt)
#define   DISABLE_PREEMPTED_VM          //!< Don't run VM as preempted
#define   DISABLE_USBSTICK_SUPPORT      //!< Don't use USB stick

namespace ev3lib::hardware::detail::lms2012 {

typedef   unsigned char         UBYTE;  //!< Basic Type used to symbolise 8  bit unsigned values
typedef   unsigned short        UWORD;  //!< Basic Type used to symbolise 16 bit unsigned values
typedef   unsigned int          ULONG;  //!< Basic Type used to symbolise 32 bit unsigned values

typedef   signed char           SBYTE;  //!< Basic Type used to symbolise 8  bit signed values
typedef   signed short          SWORD;  //!< Basic Type used to symbolise 16 bit signed values
typedef   signed int            SLONG;  //!< Basic Type used to symbolise 32 bit signed values

typedef   float                 FLOAT;  //!< Basic Type used to symbolise 32 bit floating point values

//        VM DATA TYPES

typedef   SBYTE                 DATA8;  //!< VM Type for 1 byte signed value
typedef   SWORD                 DATA16; //!< VM Type for 2 byte signed value
typedef   SLONG                 DATA32; //!< VM Type for 4 byte signed value
typedef   FLOAT                 DATAF;  //!< VM Type for 4 byte floating point value

//        INTERFACE BETWEEN SHARED LIBRARIES AND MODULES

#ifndef   DISABLE_OLD_COLOR

static const int COLORS = 4;
static const int CALPOINTS = 3;

/*! \page results Results

    Describes result from executing functions

    \verbatim */


typedef   enum
{
  OK            = 0,                    //!< No errors to report
  BUSY          = 1,                    //!< Busy - try again
  FAIL          = 2,                    //!< Something failed
  STOP          = 4                     //!< Stopped
}
RESULT;

/*  \endverbatim */


/*! \page NxtColorMemory
 *
 *  <b>     Shared Memory </b>
 *
 *  <hr size="1"/>
 *
 *
 *  \verbatim
 */

typedef   struct
{
  ULONG   Calibration[CALPOINTS][COLORS];
  UWORD   CalLimits[CALPOINTS - 1];
  UWORD   Crc;
  UWORD   ADRaw[COLORS];
  UWORD   SensorRaw[COLORS];
}
COLORSTRUCT;

/*\endverbatim
 *
 *  \n
 */

#endif

/*! \page AnalogModuleMemory
 *  <b>     Shared Memory </b>
 *
 *  <hr size="1"/>
 *
 *  It is possible to get a pointer to the raw analogue values for use in userspace
 *  this pointer will point to a struct and the layout is following:
 *
 *  \verbatim
 */

typedef   struct
{
  DATA16  InPin1[INPUTS];         //!< Analog value at input port connection 1
  DATA16  InPin6[INPUTS];         //!< Analog value at input port connection 6
  DATA16  OutPin5[OUTPUTS];       //!< Analog value at output port connection 5
  DATA16  BatteryTemp;            //!< Battery temperature
  DATA16  MotorCurrent;           //!< Current flowing to motors
  DATA16  BatteryCurrent;         //!< Current flowing from the battery
  DATA16  Cell123456;             //!< Voltage at battery cell 1, 2, 3,4, 5, and 6
#ifndef DISABLE_FAST_DATALOG_BUFFER
  DATA16  Pin1[INPUTS][DEVICE_LOGBUF_SIZE];      //!< Raw value from analog device
  DATA16  Pin6[INPUTS][DEVICE_LOGBUF_SIZE];      //!< Raw value from analog device
  UWORD   Actual[INPUTS];
  UWORD   LogIn[INPUTS];
  UWORD   LogOut[INPUTS];
#endif
#ifndef   DISABLE_OLD_COLOR
  COLORSTRUCT  NxtCol[INPUTS];
#endif
  DATA16  OutPin5Low[OUTPUTS];    //!< Analog value at output port connection 5 when connection 6 is low

  DATA8   Updated[INPUTS];

  DATA8   InDcm[INPUTS];          //!< Input port device types
  DATA8   InConn[INPUTS];

  DATA8   OutDcm[OUTPUTS];        //!< Output port device types
  DATA8   OutConn[OUTPUTS];
#ifndef DISABLE_PREEMPTED_VM
  UWORD   PreemptMilliSeconds;
#endif
}
ANALOG;

/*\endverbatim
 *
 *  \n
 */

static const size_t TYPE_NAME_LENGTH = 11;
static const size_t SYMBOL_LENGTH = 4;       //!< Symbol leng th (not including zero)

/*! \struct TYPES
 *          Device type data
 */
typedef   struct // if data type changes - remember to change "cInputTypeDataInit" !
{
  char      Name[TYPE_NAME_LENGTH + 1]; //!< Device name
  DATA8     Type;                       //!< Device type
  DATA8     Connection;
  DATA8     Mode;                       //!< Device mode
  DATA8     DataSets;
  DATA8     Format;
  DATA8     Figures;
  DATA8     Decimals;
  DATA8     Views;
  DATAF     RawMin;                     //!< Raw minimum value      (e.c. 0.0)
  DATAF     RawMax;                     //!< Raw maximum value      (e.c. 1023.0)
  DATAF     PctMin;                     //!< Percent minimum value  (e.c. -100.0)
  DATAF     PctMax;                     //!< Percent maximum value  (e.c. 100.0)
  DATAF     SiMin;                      //!< SI unit minimum value  (e.c. -100.0)
  DATAF     SiMax;                      //!< SI unit maximum value  (e.c. 100.0)
  UWORD     InvalidTime;                //!< mS from type change to valid data
  UWORD     IdValue;                    //!< Device id value        (e.c. 0 ~ UART)
  DATA8     Pins;                       //!< Device pin setup
  SBYTE     Symbol[SYMBOL_LENGTH + 1];  //!< SI unit symbol
  UWORD     Align;
}
TYPES;

/*! \page UartModuleMemory
 *
 *  <b>     Shared Memory </b>
 *
 *  <hr size="1"/>
 *
 *  It is possible to get a pointer to the uart values for use in userspace
 *  this pointer will point to a struct and the layout is following:
 *
 *  \verbatim
 */

static const size_t UART_DATA_LENGTH = MAX_DEVICE_DATALENGTH;
static const size_t UART_BUFFER_SIZE = 64;

typedef   struct
{
  TYPES   TypeData[INPUTS][MAX_DEVICE_MODES]; //!< TypeData

#ifndef DISABLE_FAST_DATALOG_BUFFER
  UWORD   Repeat[INPUTS][DEVICE_LOGBUF_SIZE];
  UBYTE   Raw[INPUTS][DEVICE_LOGBUF_SIZE][UART_DATA_LENGTH];      //!< Raw value from UART device
  UWORD   Actual[INPUTS];
  UWORD   LogIn[INPUTS];
#else
  UBYTE   Raw[INPUTS][UART_DATA_LENGTH];      //!< Raw value from UART device
#endif
  DATA8   Status[INPUTS];                     //!< Status
  DATA8   Output[INPUTS][UART_DATA_LENGTH];   //!< Bytes to UART device
  DATA8   OutputLength[INPUTS];
}
UART;

/*\endverbatim
 *
 *  \n
 */


typedef   struct
{
  DATA8     Connection[INPUTS];
  DATA8     Type[INPUTS];
  DATA8     Mode[INPUTS];
}
DEVCON;


typedef   struct
{
  TYPES   TypeData;
  UBYTE   Port;
  DATA8   Mode;
}
UARTCTL;

static const uint32_t UART_SET_CONN        = _IOWR('u',0,DEVCON);
static const uint32_t UART_READ_MODE_INFO  = _IOWR('u',1,UARTCTL);
static const uint32_t UART_NACK_MODE_INFO  = _IOWR('u',2,UARTCTL);
static const uint32_t UART_CLEAR_CHANGED   = _IOWR('u',3,UARTCTL);


/*! \page IicModuleMemory
 *
 *  <b>     Shared Memory </b>
 *
 *  <hr size="1"/>
 *
 *  It is possible to get a pointer to the iic values for use in userspace
 *  this pointer will point to a struct and the layout is following:
 *
 *  \verbatim
 */

static const size_t IIC_DATA_LENGTH = MAX_DEVICE_DATALENGTH;
static const size_t IIC_NAME_LENGTH = 8;

typedef   struct
{
  TYPES   TypeData[INPUTS][MAX_DEVICE_MODES]; //!< TypeData

#ifndef DISABLE_FAST_DATALOG_BUFFER
  UWORD   Repeat[INPUTS][DEVICE_LOGBUF_SIZE];
  DATA8   Raw[INPUTS][DEVICE_LOGBUF_SIZE][IIC_DATA_LENGTH];      //!< Raw value from IIC device
  UWORD   Actual[INPUTS];
  UWORD   LogIn[INPUTS];
#else
  DATA8   Raw[INPUTS][IIC_DATA_LENGTH];      //!< Raw value from IIC device
#endif
  DATA8   Status[INPUTS];                     //!< Status
  DATA8   Changed[INPUTS];
  DATA8   Output[INPUTS][IIC_DATA_LENGTH];    //!< Bytes to IIC device
  DATA8   OutputLength[INPUTS];
}
IIC;

/*\endverbatim
 *
 *  \n
 */


static const uint32_t IIC_PORT_CHANGED     = 0x01;       //!< Input port changed
static const uint32_t IIC_DATA_READY       = 0x08;       //!< Data is ready
static const uint32_t IIC_WRITE_REQUEST    = 0x10;       //!< Write request


typedef   struct
{
  TYPES   TypeData;
  DATA8   Port;
  DATA8   Mode;
}
IICCTL;


typedef   struct
{
  RESULT  Result;
  DATA8   Port;
  DATA8   Repeat;
  DATA16  Time;
  DATA8   WrLng;
  DATA8   WrData[IIC_DATA_LENGTH];
  DATA8   RdLng;
  DATA8   RdData[IIC_DATA_LENGTH];
}
IICDAT;


typedef   struct
{
  DATA8   Port;
  DATA16  Time;
  DATA8   Type;
  DATA8   Mode;
  DATA8   Manufacturer[IIC_NAME_LENGTH + 1];
  DATA8   SensorType[IIC_NAME_LENGTH + 1];
  DATA8   SetupLng;
  ULONG   SetupString;
  DATA8   PollLng;
  ULONG   PollString;
  DATA8   ReadLng;
}
IICSTR;


static const uint32_t IIC_SET_CONN          = _IOWR('i',2,DEVCON);
static const uint32_t IIC_READ_TYPE_INFO    = _IOWR('i',3,IICCTL);
static const uint32_t IIC_SETUP             = _IOWR('i',5,IICDAT);
static const uint32_t IIC_SET               = _IOWR('i',6,IICSTR);




static const size_t TST_PIN_LENGTH   = 8;

typedef   struct
{
  DATA8   Port;
  DATA8   Length;
  DATA8   String[TST_PIN_LENGTH + 1];
}
TSTPIN;

static const uint32_t TST_PIN_ON            = _IOWR('t',1,TSTPIN);
static const uint32_t TST_PIN_OFF           = _IOWR('t',2,TSTPIN);
static const uint32_t TST_PIN_READ          = _IOWR('t',3,TSTPIN);
static const uint32_t TST_PIN_WRITE         = _IOWR('t',4,TSTPIN);


static const size_t TST_UART_LENGTH         = UART_BUFFER_SIZE;

typedef   struct
{
  DATA32  Bitrate;
  DATA8   Port;
  DATA8   Length;
  DATA8   String[TST_UART_LENGTH];
}
TSTUART;

static const uint32_t TST_UART_ON           = _IOWR('t',5,TSTUART);
static const uint32_t TST_UART_OFF          = _IOWR('t',6,TSTUART);
static const uint32_t TST_UART_EN           = _IOWR('t',7,TSTUART);
static const uint32_t TST_UART_DIS          = _IOWR('t',8,TSTUART);
static const uint32_t TST_UART_READ         = _IOWR('t',9,TSTUART);
static const uint32_t TST_UART_WRITE        = _IOWR('t',10,TSTUART);


/*! \page UiModuleMemory
 *
 *  <b>     Shared Memory </b>
 *
 *  <hr size="1"/>
 *
 *  It is possible to get a pointer to the ui button states for use in userspace
 *  this pointer will point to a struct and the layout is following:
 *
 *  \verbatim
 */

typedef   struct
{
  DATA8   Pressed[BUTTONS];                   //!< Pressed status
}
UI;

/*\endverbatim
 *
 *  \n
 */


/*
 *                      Motor/OUTPUT Typedef
 */
struct MOTORDATA
{
  SLONG TachoCounts;
  SBYTE Speed;
  SLONG TachoSensor;
};


}
