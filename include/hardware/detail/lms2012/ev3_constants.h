/*
 * ev3constants.h
 */

#ifndef EV3CONSTANTS_H_
#define EV3CONSTANTS_H_

namespace ev3lib {
namespace hardware {
namespace detail {

namespace lms2012 {

/**
 * Copied from EV3 sources to avoid macros usage
 */
	static const int vmOUTPUTS = 4;                                             //!< Number of output ports in the system
	static const int vmINPUTS = 4;                                              //!< Number of input  ports in the system
	static const int vmBUTTONS = 6;                                             //!< Number of buttons in the system
	static const int vmLEDS = 4;                                                //!< Number of LEDs in the system

	static const int OUTPUTS = vmOUTPUTS;                                       //!< Number of output ports in the system
	static const int INPUTS = vmINPUTS;                                         //!< Number of input  ports in the system
	static const int BUTTONS = vmBUTTONS;                                       //!< Number of buttons in the system
	static const int LEDS = vmLEDS;                                             //!< Number of LEDs in the system

	static const int BUTTON_DEBOUNCE_TIME = 30;
	static const int BUTTON_START_REPEAT_TIME = 400;
	static const int BUTTON_REPEAT_TIME = 200;

	static const int LONG_PRESS_TIME = 3000;                                    //!< [mS] Time pressed before long press recognised

	static const int ADC_REF = 5000;                                            //!< [mV]  maximal value on ADC
	static const int ADC_RES = 4095;                                            //!< [CNT] maximal count on ADC

	static const int IN1_ID_HYSTERESIS = 50;                                    //!< [mV]  half of the span one Id takes up on input connection 1 voltage
	static const int OUT5_ID_HYSTERESIS = 100;                                  //!< [mV]  half of the span one Id takes up on output connection 5 voltage

	static const int DEVICE_UPDATE_TIME = 1000000;                              //!< Min device (sensor) update time [nS]
	static const int DELAY_TO_TYPEDATA = 10000;                                 //!< Time from daisy chain active to upload type data [mS]
	static const int DAISYCHAIN_MODE_TIME = 10;                                 //!< Time for daisy chain change mode [mS]
	static const int MAX_FILE_HANDLES = 64;                                     //!< Max number of down load file handles
	static const int MIN_HANDLE = 3;                                            //!< Min file handle to close

	static const int ID_LENGTH = 7;                                             //!< Id length  (BT MAC id) (incl. zero terminator)
	static const int NAME_LENGTH = 12;                                          //!< Name length (not including zero termination)

	static const int ERROR_BUFFER_SIZE = 8;                                     //!< Number of errors in buffer

	static constexpr const char* PWM_DEVICE = "lms_pwm";             	        //!< PWM device name
	static constexpr const char* PWM_DEVICE_NAME = "/dev/lms_pwm";		        //!< PWM device file name

	static constexpr const char* MOTOR_DEVICE = "lms_motor";                    //!< TACHO device name
	static constexpr const char* MOTOR_DEVICE_NAME = "/dev/lms_motor";          //!< TACHO device file name

	static constexpr const char* ANALOG_DEVICE = "lms_analog";                  //!< ANALOG device name
	static constexpr const char* ANALOG_DEVICE_NAME = "/dev/lms_analog";        //!< ANALOG device file name

	static constexpr const char* POWER_DEVICE = "lms_power";                    //!< POWER device name
	static constexpr const char* POWER_DEVICE_NAME = "/dev/lms_power";          //!< POWER device file name

	static constexpr const char* DCM_DEVICE = "lms_dcm";                        //!< DCM device name
	static constexpr const char* DCM_DEVICE_NAME = "/dev/lms_dcm";              //!< DCM device file name

	static constexpr const char* UI_DEVICE = "lms_ui";                          //!< UI device name
	static constexpr const char* UI_DEVICE_NAME = "/dev/lms_ui";                //!< UI device file name

	static constexpr const char* LCD_DEVICE = "lms_display";                    //!< DISPLAY device name
	//static constexpr const char* LCD_DEVICE_NAME = "/dev/lms_display";        //!< DISPLAY device file name
	static constexpr const char* LCD_DEVICE_NAME = "/dev/fb0";                  //!< DISPLAY device file name

	static constexpr const char* UART_DEVICE = "lms_uart";                      //!< UART device name
	static constexpr const char* UART_DEVICE_NAME = "/dev/lms_uart";            //!< UART device file name

	static constexpr const char* USBDEV_DEVICE = "lms_usbdev";                  //!< USB device
	static constexpr const char* USBDEV_DEVICE_NAME = "/dev/lms_usbdev";        //!< USB device

	static constexpr const char* USBHOST_DEVICE = "lms_usbhost";                //!< USB host
	static constexpr const char* USBHOST_DEVICE_NAME = "/dev/lms_usbhost";      //!< USB host

	static constexpr const char* SOUND_DEVICE = "lms_sound";                    //!< SOUND device name
	static constexpr const char* SOUND_DEVICE_NAME = "/dev/lms_sound";          //!< SOUND device

	static constexpr const char* IIC_DEVICE = "lms_iic";                        //!< IIC device name
	static constexpr const char* IIC_DEVICE_NAME = "/dev/lms_iic";              //!< IIC device

	static constexpr const char* BT_DEVICE = "lms_bt";                          //!< BT device name
	static constexpr const char* BT_DEVICE_NAME = "/dev/lms_bt";                //!< BT device

	static constexpr const char* UPDATE_DEVICE = "lms_update";                  //!< UPDATE device name
	static constexpr const char* UPDATE_DEVICE_NAME = "/dev/lms_update";        //!< UPDATE device

	static constexpr const char* TEST_PIN_DEVICE = "lms_tst_pin";               //!< TEST pin device name
	static constexpr const char* TEST_PIN_DEVICE_NAME = "/dev/lms_tst_pin";     //!< TEST pin device file name

	static constexpr const char* TEST_UART_DEVICE = "lms_tst_uart";             //!< TEST UART device name
	static constexpr const char* TEST_UART_DEVICE_NAME = "/dev/lms_tst_uart";   //!< TEST UART device file name

	static const int MAX_DEVICE_MODES = 8;                                      //!< Max number of modes in one device
	static const int MAX_DEVICE_DATASETS = 8;                                   //!< Max number of data sets in one device
	static const int MAX_DEVICE_DATALENGTH = 32;                                //!< Max device data length

	static const int LOGBUFFER_SIZE = 1000;                                     //!< Min log buffer size
	static const int DEVICE_LOGBUF_SIZE = 300;                                  //!< Device log buffer size (black layer buffer)
	static const int MIN_LIVE_UPDATE_TIME = 10;                                 //!< [mS] Min sample time when live update

	//UART
	static const int UART_PORT_CHANGED  = 0x01;        //!< Input port changed
	static const int UART_DATA_READY    = 0x08;        //!< Data is ready
	static const int UART_WRITE_REQUEST = 0x10;        //!< Write request

}
} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3CONSTANTS_H_ */
