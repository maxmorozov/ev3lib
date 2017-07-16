#pragma once

#include <limits>

#include <hardware/sensor/scale/AccelScaleSelector.h>
#include <hardware/sensor/scale/GyroScaleSelector.h>
#include <hardware/sensor/eeprom/AccelEepromWriter.h>
#include <hardware/sensor/eeprom/GyroEepromWriter.h>

#include "UartSensor.h"

namespace ev3lib {
namespace hardware {

	class ImuLsm6ds3 : public UartSensor, public AccelScaleSelector, public GyroScaleSelector, public AccelEepromWriter, public GyroEepromWriter {
	private:
		template<size_t sampleSize> friend class BaseSensorMode;
		friend class CombinedMode;
		friend class AccelerometerMode;
		friend class GyroMode;
	public:
		static const long SCALE_SWITCH_DELAY = 10;

		//Return device to the state right after power on
	    static const uint8_t DEVICE_RESET  = 0x11;

	    //Accelerometer sensitivity
	    static const uint8_t ACC_SCALE_2G  = 0x20;
	    static const uint8_t ACC_SCALE_4G  = 0x21;
	    static const uint8_t ACC_SCALE_8G  = 0x22;
	    static const uint8_t ACC_SCALE_16G = 0x23;

	    //Gyroscope sensitivity
	    static const uint8_t GYRO_SCALE_245DPS  = 0x30;
	    static const uint8_t GYRO_SCALE_500DPS  = 0x31;
	    static const uint8_t GYRO_SCALE_1000DPS = 0x32;
	    static const uint8_t GYRO_SCALE_2000DPS = 0x33;
	    static const uint8_t GYRO_SCALE_125DPS  = 0x34;

	    //Write calibration matrix into EEPROM
	    static const uint8_t CALIBRATE_ACC_2G  = 0x40;
	    static const uint8_t CALIBRATE_ACC_4G  = 0x41;
	    static const uint8_t CALIBRATE_ACC_8G  = 0x42;
	    static const uint8_t CALIBRATE_ACC_16G = 0x43;

	    static const uint8_t CALIBRATE_GYRO_245DPS  = 0x50;
	    static const uint8_t CALIBRATE_GYRO_500DPS  = 0x51;
	    static const uint8_t CALIBRATE_GYRO_1000DPS = 0x52;
	    static const uint8_t CALIBRATE_GYRO_2000DPS = 0x53;
	    static const uint8_t CALIBRATE_GYRO_125DPS  = 0x54;

	    static const int ACCEL_SCALE = std::numeric_limits<short>::max() + 1;

	private:
	    template<size_t sample_size, size_t modeNo>
	    class BaseSensorMode : public SensorMode {
	    public:
	    	static const size_t SAMPLE_SIZE = sample_size;
	    	static const size_t MODE_NO = modeNo;

	    protected:
	    	ImuLsm6ds3* m_sensor;

	    	//Apply the current scale to the sample
	    	virtual void scale(int16_t* buffer, float* sample, size_t offset) = 0;
	    public:
	    	BaseSensorMode(ImuLsm6ds3* sensor) : m_sensor(sensor) {}

			virtual size_t sampleSize() const override {
				return SAMPLE_SIZE;
			}
			virtual void fetchSample(float* sample, size_t offset) override {
				short buffer[SAMPLE_SIZE];

				m_sensor->readSample(modeNo, buffer, SAMPLE_SIZE);
				scale(buffer, sample, offset);
			}
	    };


	    /**
	     * 3d accelerometer and 3d gyroscope sample
	     */
	    class CombinedMode : public BaseSensorMode<6, 0> {
	    protected:
	    	//Apply the current scale to the sample
	    	virtual void scale(int16_t* buffer, float* sample, size_t offset) {
	    		//Accelerometer
	    		for (size_t i = 0; i < 3; ++i) {
	    			sample[offset + i] = buffer[i] * m_sensor->getAccelScale();
	    		}
	    		for (size_t i = 3; i < SAMPLE_SIZE; ++i) {
	    			sample[offset + i] = buffer[i] * m_sensor->getGyroScale();
	    		}
	    	}

	    public:
	    	CombinedMode(ImuLsm6ds3* sensor): BaseSensorMode(sensor) {}

	    	virtual std::string getName() const override {
				return "ALL";
			}

	    };

	    /**
	     * Acceleration measurement mode
	     */
	    class AccelerometerMode : public BaseSensorMode<3, 1> {
	    protected:
	    	//Apply the current scale to the sample
	    	virtual void scale(int16_t* buffer, float* sample, size_t offset) {
	    		//Accelerometer
	    		for (size_t i = 0; i < SAMPLE_SIZE; ++i) {
	    			sample[offset + i] = buffer[i] * m_sensor->getAccelScale();
	    		}
	    	}

	    public:
	    	AccelerometerMode(ImuLsm6ds3* sensor): BaseSensorMode(sensor) {}

	    	virtual std::string getName() const override {
				return "Acceleration";
			}
	    };

	    class GyroMode : public BaseSensorMode<3, 2> {
	    protected:
	    	//Apply the current scale to the sample
	    	virtual void scale(int16_t* buffer, float* sample, size_t offset) {
	    		//Accelerometer
	    		for (size_t i = 0; i < SAMPLE_SIZE; ++i) {
	    			sample[offset + i] = buffer[i] * m_sensor->getGyroScale();
	    		}
	    	}

	    public:
	    	GyroMode(ImuLsm6ds3* sensor): BaseSensorMode(sensor) {}

	    	virtual std::string getName() const override {
				return "Rate";
			}
	    };

	private:
		static const float gyroScale[5];    //in degree per second / digit
		static const float accelScale[4];   //in g / digit

	    size_t m_accelScale = 0;
	    size_t m_gyroScale = 0;
	    bool m_rawMode;

	    static std::vector<std::unique_ptr<SensorMode>> createModes(ImuLsm6ds3* sensor);

	    bool writeEeprom(int writeCommand, const int16_t* data, size_t size);

	    bool setScale(int scaleCommand);

	    float getAccelScale() const;
	    float getGyroScale() const;

	    //Set the required mode and fetch sample
	    void readSample(size_t mode, int16_t* buffer, size_t sampleSize);

	public:
	    ImuLsm6ds3(std::unique_ptr<detail::UartPort>&& port, bool rawMode = false);
	    ImuLsm6ds3(ImuLsm6ds3&& other);

	    void reset();

	    //Change scale support

	    /**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setAccelerometerScale(size_t scaleNo) override;

		/**
		 * Changes the gyroscope full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
		virtual bool setGyroscopeScale(size_t scaleNo) override;

		//EEPROM

		/**
		 * Update accelerometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
		virtual bool writeAccelerometerEeprom(size_t scaleNo, const int16_t* data, size_t size) override;

		/**
		 * Update gyroscope EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
		virtual bool writeGyroscopeEeprom(size_t scaleNo, const int16_t* data, size_t size) override;
	};


}}
