#pragma once

#include <limits>

#include <hardware/sensor/scale/AccelScaleSelector.h>
#include <hardware/sensor/scale/GyroScaleSelector.h>
#include <hardware/sensor/eeprom/AccelEepromWriter.h>
#include <hardware/sensor/eeprom/GyroEepromWriter.h>
#include <utils/str_const.h>

#include "UartSensor.h"

namespace ev3lib {
namespace hardware {

	class ImuLsm6ds3 : public UartSensor, public AccelScaleSelector, public GyroScaleSelector, public AccelEepromWriter, public GyroEepromWriter {
	private:
		template<size_t sampleSize> friend class BaseSensorMode;
		friend class CombinedMode;
		friend class AccelerometerMode;
		friend class GyroMode;

        struct Mode {
            str_const name;
            std::size_t sampleSize;
            std::size_t modeId;
        };

        static const constexpr Mode modes[3] = {
                {str_const("ALL"), 6, 0},
                {str_const("Acceleration"), 3, 1},
                {str_const("Rate"), 3, 2}
        };

        static constexpr size_t maxSampleSize() {
            size_t result = 0;
            for (Mode mode: modes) {
                result = std::max(result, mode.sampleSize);
            }
            return result;
        }

        static constexpr size_t getModeId(size_t index) {
            if (index >= count_of(modes))
                throw std::out_of_range("");
            return modes[index].modeId;
        }

	public:
		//static const int SCALE_SWITCH_DELAY = 10;
		enum {SCALE_SWITCH_DELAY = 10};

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

	    static constexpr int ACCEL_SCALE = std::numeric_limits<short>::max() + 1;

	private:
        void scaleCombined(const int16_t* buffer, float* sample, size_t offset);
        void scaleAccel(const int16_t* buffer, float* sample, size_t offset);
        void scaleGyro(const int16_t* buffer, float* sample, size_t offset);


	private:
		static const float gyroScale[5];    //in degree per second / digit
		static const float accelScale[4];   //in g / digit

	    size_t m_accelScale = 0;
	    size_t m_gyroScale = 0;
	    bool m_rawMode;

	    static std::vector<ModeInfo> createModes();

	    bool writeEeprom(int writeCommand, const int16_t* data, size_t size);

	    bool setScale(int scaleCommand);

	    float getAccelScale() const;
	    float getGyroScale() const;

	    //Set the required mode and fetch sample
	    void readSample(size_t mode, int16_t* buffer, size_t sampleSize);

	public:
	    explicit ImuLsm6ds3(std::unique_ptr<detail::UartPort>&& port, bool rawMode = false);
	    ImuLsm6ds3(ImuLsm6ds3&& other) noexcept;

	    void reset();


		/** Fetches a sample from a sensor or filter.
		 * @param sample
		 * The array to store the sample in.
		 * @param offset
		 * The elements of the sample are stored in the array starting at the offset position.
		 */
		void fetchSample(float* sample, size_t offset) override;

		//Change scale support

	    /**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
        bool setAccelerometerScale(size_t scaleNo) override;

		/**
		 * Changes the gyroscope full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
        bool setGyroscopeScale(size_t scaleNo) override;

		//EEPROM

		/**
		 * Update accelerometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
        bool writeAccelerometerEeprom(size_t scaleNo, const int16_t* data, size_t size) override;

		/**
		 * Update gyroscope EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
        bool writeGyroscopeEeprom(size_t scaleNo, const int16_t* data, size_t size) override;
	};


}}
