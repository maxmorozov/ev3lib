/*
 * device_manager.h
 *
 *  Created on: 11 ���. 2014 �.
 *      Author: Max
 */

#ifndef EV3LIB_DEVICE_MANAGER_H_
#define EV3LIB_DEVICE_MANAGER_H_

#include <utilities.h>
#include <stddef.h>
#include <memory>

namespace ev3lib {
namespace hardware {
namespace detail {

	//EV3 hardware type
	enum class SensorType: char {
	    NxtTouch                =   1,  //!< Device is NXT touch sensor
	    NxtLight                =   2,  //!< Device is NXT light sensor
	    NxtSound                =   3,  //!< Device is NXT sound sensor
	    NxtColor                =   4,  //!< Device is NXT color sensor
	    NxtUltrasonic           =   5,  //!< Device is NXT ultra-sonic sensor
	    NxtTemperature          =   6,  //!< Device is NXT ultra-sonic sensor
	    Tacho                   =   7,  //!< Device is a tacho motor
	    MiniTacho               =   8,  //!< Device is a mini tacho motor
	    NewTacho                =   9,  //!< Device is a new tacho motor

	    Touch                   =  16,
	    Test                    =  21,
	    Color                   =  29,
	    UltraSonic              =  30,
	    Gyro                    =  32,
	    IR                      =  33,

	    ThirdPartyStart         =  50,
	    ThirdPartyEnd           =  99,

	    I2cUnknown              = 100,
	    NxtTest                 = 101,  //!< Device is a NXT ADC test sensor
	    NxtI2c                  = 123,  //!< Device is NXT IIC sensor
	    Terminal                = 124,  //!< Port is connected to a terminal
	    Unknown                 = 125,  //!< Port not empty but type has not been determined
	    None                    = 126,  //!< Port empty or not available
	    Error                   = 127  //!< Port not empty and type is invalid
	};

	enum class ConnectionType: char {
		  Unknown               = 111,  //!< Connection is fake (test)

		  DaisyChain            = 117,  //!< Connection is daisy chained
		  NxtColor              = 118,  //!< Connection type is NXT color sensor
		  NxtDumb               = 119,  //!< Connection type is NXT analog sensor
		  NxtI2c                = 120,  //!< Connection type is NXT IIC sensor

		  InputDumb             = 121,  //!< Connection type is LMS2012 input device with ID resistor
		  InputUart             = 122,  //!< Connection type is LMS2012 UART sensor

		  OutputDumb            = 123,  //!< Connection type is LMS2012 output device with ID resistor
		  OutputIntelligent     = 124,  //!< Connection type is LMS2012 output device with communication
		  OutputTacho           = 125,  //!< Connection type is LMS2012 tacho motor with series ID resistance

		  None                  = 126,  //!< Port empty or not available
		  Error                 = 127   //!< Port not empty and type is invalid
	};

	enum class AnalogMode : unsigned char {
		None = '-',
		Float = 'f',
		Set = '0',
		Automatic = 'a',
		Connected = 'c',
		Disconnected = 'd',
		ColorFull = 0x0D,
		ColorRed = 0x0E,
		ColorGreen = 0x0F,
		ColorBlue = 0x10,
		ColorNone = 0x11,
		ColorExit = 0x12,
		Pin1 = 0x01,
		Pin5 = 0x02
	};

	enum class PortType {
		Motor = 0,
		Sensor = 1
	};

	struct AnalogPort: public destructible {
	    /**
	     * return the voltage present on pin 6 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual int getPin6() const = 0;

	    /**
	     * return the voltage present on pin 1 of the sensor port
	     * @return raw ADC voltage reading
	     */
		virtual int getPin1() const = 0;

	    /**
	     * sets the sensor type.
	     * @return success status
	     */
		virtual bool setType(int mode) = 0;
	};

	/**
	 * Provides information about types of connected sensors and allows to get their values
	 */
	struct SensorsManager: public destructible {
		virtual SensorType getSensorType(size_t port) const = 0;
		virtual ConnectionType getConnectionType(size_t port) const = 0;

		virtual void setPortMode(size_t port, PortType type, AnalogMode mode) = 0;

		virtual std::unique_ptr<AnalogPort> getAnalogPort(size_t port) = 0;

		/**
		 * Current flowing from the battery
		 */
		virtual short getMotorCurrent() const = 0;

		/**
		 * Current flowing from the battery
		 */
		virtual short getBatteryCurrent() const = 0;
	};

	inline AnalogMode operator | (AnalogMode left, AnalogMode right) {
		return AnalogMode(int(left) | int(right));
	}

}}}




#endif /* EV3LIB_DEVICE_MANAGER_H_ */
