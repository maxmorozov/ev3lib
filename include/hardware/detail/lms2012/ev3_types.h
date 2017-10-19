/*
 * ev3_types.h
 */

#ifndef EV3_TYPES_H_
#define EV3_TYPES_H_

#include <sys/ioctl.h>
#include <hardware/detail/lms2012/ev3_constants.h>

//#define   DISABLE_OLD_COLOR             //!< Don't support NXT color sensor
//#define   DISABLE_FAST_DATALOG_BUFFER
#define   UART1_FAKE_INTERRUPT          //!< Don't use real interrupt on UART1 (linux prompt)
#define   DISABLE_PREEMPTED_VM          //!< Don't run VM as preempted
#define   DISABLE_USBSTICK_SUPPORT      //!< Don't use USB stick

namespace ev3lib {
namespace hardware {
namespace detail {

namespace lms2012 {

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

static const int TYPE_NAME_LENGTH = 11;
static const int SYMBOL_LENGTH = 4;       //!< Symbol leng th (not including zero)

/*! \struct TYPES
 *          Device type data
 */
typedef   struct // if data type changes - remember to change "cInputTypeDataInit" !
{
  SBYTE     Name[TYPE_NAME_LENGTH + 1]; //!< Device name
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

static const int UART_DATA_LENGTH = MAX_DEVICE_DATALENGTH;
static const int UART_BUFFER_SIZE = 64;

typedef   struct
{
  TYPES   TypeData[INPUTS][MAX_DEVICE_MODES]; //!< TypeData

#ifndef DISABLE_FAST_DATALOG_BUFFER
  UWORD   Repeat[INPUTS][DEVICE_LOGBUF_SIZE];
  DATA8   Raw[INPUTS][DEVICE_LOGBUF_SIZE][UART_DATA_LENGTH];      //!< Raw value from UART device
  UWORD   Actual[INPUTS];
  UWORD   LogIn[INPUTS];
#else
  DATA8   Raw[INPUTS][UART_DATA_LENGTH];      //!< Raw value from UART device
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
  DATA8   Port;
  DATA8   Mode;
}
UARTCTL;

static const uint32_t UART_SET_CONN        = _IOWR('u',0,DEVCON);
static const uint32_t UART_READ_MODE_INFO  = _IOWR('u',1,UARTCTL);
static const uint32_t UART_NACK_MODE_INFO  = _IOWR('u',2,UARTCTL);
static const uint32_t UART_CLEAR_CHANGED   = _IOWR('u',3,UARTCTL);


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
} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3_TYPES_H_ */
