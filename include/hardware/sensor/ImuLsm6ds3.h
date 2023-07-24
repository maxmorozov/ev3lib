#pragma once

#include <limits>

#include <hardware/sensor/scale/AccelScaleSelector.h>
#include <hardware/sensor/scale/GyroScaleSelector.h>
#include <hardware/sensor/eeprom/AccelEepromWriter.h>
#include <hardware/sensor/eeprom/GyroEepromWriter.h>
#include <utils/str_const.h>

#include <hardware/sensor/UartSensor.h>

namespace ev3lib::hardware::sensor {

	class ImuLsm6ds3 : public UartSensor,
            public scale::AccelScaleSelector, public scale::GyroScaleSelector,
            public eeprom::AccelEepromWriter, public eeprom::GyroEepromWriter {
	public:
		enum class GyroScale : size_t {
			SCALE_245DPS  = 0,
			SCALE_500DPS  = 1,
			SCALE_1000DPS = 2,
			SCALE_2000DPS = 3,
			SCALE_125DPS  = 4
		};
		enum class AccelScale : size_t {
			SCALE_2G  = 0,
			SCALE_4G  = 1,
			SCALE_8G  = 2,
			SCALE_16G = 3
		};
	private:
		template<size_t sampleSize> friend class BaseSensorMode;
		friend class CombinedMode;
		friend class AccelerometerMode;
		friend class GyroMode;

        struct Mode {
            utils::str_const name;
            std::size_t sampleSize;
            std::size_t modeId;
        };

        static const constexpr Mode modes[3] = {
                {utils::str_const("ALL"), 6, 0},
                {utils::str_const("Acceleration"), 3, 1},
                {utils::str_const("Rate"), 3, 2}
        };

        static constexpr size_t maxSampleSize() {
            size_t result = 0;
            for (Mode mode: modes) {
                result = std::max(result, mode.sampleSize);
            }
            return result;
        }

        static constexpr size_t getModeId(size_t index) {
            if (index >= utils::count_of(modes))
                throw std::out_of_range("");
            return modes[index].modeId;
        }

	private:
		static constexpr int SCALE_SWITCH_DELAY = 10;

		//Return device to the state right after power on
	    static constexpr uint8_t DEVICE_RESET  = 0x11;

	    //Accelerometer sensitivity
	    static constexpr uint8_t ACC_SCALE_2G  = 0x20;
	    static constexpr uint8_t ACC_SCALE_4G  = 0x21;
	    static constexpr uint8_t ACC_SCALE_8G  = 0x22;
	    static constexpr uint8_t ACC_SCALE_16G = 0x23;

	    //Gyroscope sensitivity
	    static constexpr uint8_t GYRO_SCALE_245DPS  = 0x30;
	    static constexpr uint8_t GYRO_SCALE_500DPS  = 0x31;
	    static constexpr uint8_t GYRO_SCALE_1000DPS = 0x32;
	    static constexpr uint8_t GYRO_SCALE_2000DPS = 0x33;
	    static constexpr uint8_t GYRO_SCALE_125DPS  = 0x34;

	    //Write calibration matrix into EEPROM
	    static constexpr uint8_t CALIBRATE_ACC_2G  = 0x40;
	    static constexpr uint8_t CALIBRATE_ACC_4G  = 0x41;
	    static constexpr uint8_t CALIBRATE_ACC_8G  = 0x42;
	    static constexpr uint8_t CALIBRATE_ACC_16G = 0x43;

	    static constexpr uint8_t CALIBRATE_GYRO_245DPS  = 0x50;
	    static constexpr uint8_t CALIBRATE_GYRO_500DPS  = 0x51;
	    static constexpr uint8_t CALIBRATE_GYRO_1000DPS = 0x52;
	    static constexpr uint8_t CALIBRATE_GYRO_2000DPS = 0x53;
	    static constexpr uint8_t CALIBRATE_GYRO_125DPS  = 0x54;

	    static constexpr int ACCEL_SCALE = std::numeric_limits<short>::max() + 1;

	private:
		void scaleData(std::span<const int16_t> buffer, std::span<float> sample);
        void scaleCombined(std::span<const int16_t> source, std::span<float> target);
		static void scale(std::span<const int16_t> source, std::span<float> target, float scale);

	private:
		static const float gyroScale[5];    //in degree per second / digit
		static const float accelScale[4];   //in g / digit

	    size_t m_accelScale = 0;
	    size_t m_gyroScale = 0;
	    bool m_rawMode;

	    static std::vector<ModeInfo> createModes();

	    bool writeEeprom(uint8_t writeCommand, std::span<const int16_t> data);

	    bool updateScale(uint8_t scaleCommand);

	    float getAccelScale() const;
	    float getGyroScale() const;

	    //Set the required mode and fetch sample
	    void readSample(std::span<int16_t> buffer);

    protected:
        void switchMode(size_t newMode) override;

	public:
	    explicit ImuLsm6ds3(std::unique_ptr<port::UartPort> port, bool rawMode = false);

	    void reset();


		/** Fetches a sample from a sensor or filter.
		 * @param sample The buffer to store the sample in.
		 */
		void fetchSample(std::span<float> sample) override;

		//Change scale support

		/**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scale scale enum constant
		 * @return true if the current scale range has been successfully changed
		 */
		bool setScale(AccelScale scale)
		{
			return setAccelerometerScale(static_cast<size_t>(scale));
		}

		/**
		 * Changes the gyroscope full-scale range
		 *
		 * @param scale scale enum constant
		 * @return true if the current scale range has been successfully changed
		 */
		bool setScale(GyroScale scale)
		{
			return setGyroscopeScale(static_cast<size_t>(scale));
		}

	    /**
		 * Changes the accelerometer full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
        bool setAccelerometerScale(size_t scaleNo) override;

		/**
		 * Returns number of supported scales
		 *
		 * @return number of scales supported by the sensor
		 */
		size_t getAccelerometerScales() const override;

		/**
		 * Changes the gyroscope full-scale range
		 *
		 * @param scaleNo scale range index
		 * @return true if the current scale range has been successfully changed
		 */
        bool setGyroscopeScale(size_t scaleNo) override;

		/**
		 * Returns number of supported scales
		 *
		 * @return number of scales supported by the sensor
		 */
		size_t getGyroscopeScales() const override;

		//EEPROM

		/**
		 * Update accelerometer EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @return true if the EEPROM data has been successfully written
		 */
        [[nodiscard]]
        bool writeAccelerometerEeprom(size_t scaleNo, std::span<const int16_t> data) override;

		/**
		 * Update gyroscope EEPROM
		 *
		 * @param scaleNo scale index
		 * @param data EEPROM data (4x3 matrix of 16-bit integers)
		 * @param size size of EEPROM data in words
		 * @return true if the EEPROM data has been successfully written
		 */
        [[nodiscard]]
        bool writeGyroscopeEeprom(size_t scaleNo, std::span<const int16_t> data) override;
	};


}
