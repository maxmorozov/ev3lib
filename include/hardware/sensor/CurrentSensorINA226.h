#pragma once

#include <cstdint>
#include <vector>
#include <utils/str_const.h>
#include <hardware/sensor/I2CSensor.h>
#include <hardware/sensor/SensorModes.h>

namespace ev3lib::hardware::sensor {

    class CurrentSensorINA226 : protected I2CSensor, public SensorModes {
    private:
        static constexpr int VBUS_MAX = 36;

        static constexpr float VSHUNT_MAX = 0.08192f;
        static constexpr float VSHUNT_LSB = 0.0025f; //in mV

        //Internal current calculation factor
        static constexpr float CURRENT_SCALING_FACTOR = 0.00512f;

        //Voltage LSB in V
        static constexpr float VOLTAGE_LSB = 0.00125f;

        static constexpr uint8_t REG_CONFIG = 0x00;
        static constexpr uint8_t REG_SHUNT_VOLTAGE = 0x01;
        static constexpr uint8_t REG_BUS_VOLTAGE = 0x02;
        static constexpr uint8_t REG_POWER = 0x03;
        static constexpr uint8_t REG_CURRENT = 0x04;
        static constexpr uint8_t REG_CALIBRATION = 0x05;
        static constexpr uint8_t REG_MASK_ENABLE = 0x06;
        static constexpr uint8_t REG_ALERT_LIMIT = 0x07;
        static constexpr uint8_t REG_MANUFACTURER_ID = 0xFE;
        static constexpr uint8_t REG_DIR_ID = 0xFF;

        //Mask register fiels
        static constexpr uint16_t BIT_SOL = 0x8000;   //Shunt Voltage Over-Voltage
        static constexpr uint16_t BIT_SUL = 0x4000;   //Shunt Voltage Under-Voltage
        static constexpr uint16_t BIT_BOL = 0x2000;   //Bus Voltage Over-Voltage
        static constexpr uint16_t BIT_BUL = 0x1000;   //Bus Voltage Under-Voltage
        static constexpr uint16_t BIT_POL = 0x0800;   //Power Over-Limit
        static constexpr uint16_t BIT_CNVR = 0x0400;  //Conversion Ready
        static constexpr uint16_t BIT_AFF = 0x0010;   //Alert Function Flag
        static constexpr uint16_t BIT_CVRF = 0x0008;  //Conversion Ready Flag
        static constexpr uint16_t BIT_OVF = 0x0004;   //Math Overflow Flag
        static constexpr uint16_t BIT_APOL = 0x0002;  //Alert Polarity bit; sets the Alert pin polarity.
        static constexpr uint16_t BIT_LEN = 0x0001;   //Alert Latch Enable; configures the latching feature of the Alert pin and Alert Flag bits.

    public:
        //Default I2C address
        //EV3 uses 8-bit I2C address, but the INA219 datasheet specifies 7-bit address, so we need to double it
        static constexpr int DEFAULT_ADDRESS = 0x80; //0x40 for Arduino;

        //Average mode
        enum class Average : uint8_t {
            AVERAGES_1 = 0,
            AVERAGES_4 = 1,
            AVERAGES_16 = 2,
            AVERAGES_64 = 3,
            AVERAGES_128 = 4,
            AVERAGES_256 = 5,
            AVERAGES_512 = 6,
            AVERAGES_1024 = 7
        };

        //Bus voltage conversion time
        enum class BusConversionTime : uint8_t {
            TIME_140US = 0,
            TIME_204US = 1,
            TIME_332US = 2,
            TIME_588US = 3,
            TIME_1100US = 4,
            TIME_2116US = 5,
            TIME_4156US = 6,
            TIME_8244US = 7
        };

        //Shunt voltage conversion time
        enum class ShuntConversionTime : uint8_t {
            TIME_140US = 0,
            TIME_204US = 1,
            TIME_332US = 2,
            TIME_588US = 3,
            TIME_1100US = 4,
            TIME_2116US = 5,
            TIME_4156US = 6,
            TIME_8244US = 7
        };

        // Values for operating mode
        enum class Mode : uint8_t {
            POWER_DOWN = 0,          // power down
            SHUNT_TRIG = 1,          // shunt voltage triggered
            BUS_TRIG = 2,            // bus voltage triggered
            SHUNT_BUS_TRIG = 3,      // shunt and bus voltage triggered
            ADC_OFF = 4,             // ADC off
            SHUNT_CONT = 5,          // shunt voltage continuous
            BUS_CONT = 6,            // bus voltage continuous
            SHUNT_BUS_CONT = 7       // shunt and bus voltage continuous
        };

    private:
        //Shunt value in Ohm
        float m_shuntValue;
        int16_t m_calibrationValue;

        // The following multipliers are used to convert raw current and power
        // values to mA and mW, taking into account the current config settings
        float m_currentMultiplier_mA;
        float m_currentOffset_mA;
        float m_powerMultiplier_mW;

        float m_voltageMultiplier_V;
        float m_voltageOffset_V;

        std::vector<std::unique_ptr<SensorMode>> m_modes;
        size_t m_currentMode = 0;

        bool isValidMode(size_t mode) const;

        std::unique_ptr<SensorMode>& currentMode() {
            return m_modes[m_currentMode];
        }

        const std::unique_ptr<SensorMode>& currentMode() const {
            return m_modes[m_currentMode];
        }

        int16_t calculateCalibrationRegister(float maxCurrent) const;

        /**
         * Calculates the current conversion ratio.
         * Transforms the raw units to mA.
         *
         * @param calibrationValue the calibration register value
         * @return the current conversion ratio.
         */
        float calculateCurrentMultiplier(int16_t calibrationValue) const;

    public:
        explicit CurrentSensorINA226(std::unique_ptr<port::I2CPort> port)
                : CurrentSensorINA226(std::move(port), DEFAULT_ADDRESS) {
        }

        CurrentSensorINA226(std::unique_ptr<port::I2CPort> port, uint8_t address)
                : CurrentSensorINA226(std::move(port), address, port::SensorType::LOWSPEED) {
        }


        /**
         * Creates I2C sensor instance.<br/>
         *
         * Addresses use the standard Lego/NXT format and are in the range 0x2-0xfe.
         * The low bit must always be zero. Some data sheets (and older versions
         * of leJOS) may use i2c 7 bit format (0x1-0x7f) in which case this address
         * must be shifted left one place to be used with this function.
         * <p/>
         * Device type for I2C sensor can be: LOWSPEED, LOWSPEED_9V, HIGHSPEED, HIGHSPEED_9V
         * Lego EV3 have high value pull-up resistors, so I2C rise time is quite big, and HIGHSPEED, HIGHSPEED_9V usually will not work.
         *
         * @param port I2C port object from the device manager
         * @param address 0x02 to 0xfe
         * @param type device type.
         */
        CurrentSensorINA226(std::unique_ptr<port::I2CPort> port, uint8_t address, port::SensorType type);

        /**
         * Initializes the sensor with the maximum expected current value in A
         *
         * @param shuntValue shunt value in Ohm
         * @param maxCurrent max expected current in A
         * @param currentRatio the current correction coefficient
         * @param currentOffset the zero current offset in mA
         * @param voltageRatio the voltage correction coefficient
         * @param voltageOffset the zero voltage offset in V
         */
        void calibrate(float shuntValue, float maxCurrent, float currentRatio, float currentOffset, float voltageRatio, float voltageOffset);

        /**
         * Setup reading mode.
         * Measure time is (bus time + shunt time) * average count.
         *
         * @param avg number of samples to calculate average
         * @param busConvTime bus voltage conversion time constant
         * @param shuntConvTime shunt volatge conversion time constante
         * @param mode operating mode constant
         */
        void configure(Average avg, BusConversionTime busConvTime, ShuntConversionTime shuntConvTime, Mode mode);

        /**
         * Fetches a sample from a sensor or filter.
         *
         * @param sample The buffer to store the sample in.
         */
        void fetchSample(gsl::span<float> sample) override;

        /**
         * Return a list of string descriptions for the sensors available modes.
         * @return list of string descriptions
         */
        std::vector<std::string> getAvailableModes() const override;

        /**
         * Sets the current mode for fetching samples
         * @param mode the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
         */
        void setCurrentMode(size_t mode) override;

        /**
         * Sets the current mode for fetching samples
         * @param modeName the name of the mode. name corresponds with the item value of the list from getAvailableModes().
         */
        void setCurrentMode(const std::string& modeName) override;

        /**
         * Gets the index number of the current mode.
         * @return the index number of the mode. Index number corresponds with the item order of the list from getAvailableModes().
         */
        size_t getCurrentMode() const override {
            return m_currentMode;
        }

        /**
         * Gets the number of supported modes
         * @return the number of supported modes
         */
        size_t getModeCount() const override {
            return m_modes.size();
        }

        /**
         * return a string description of this sensor mode
         * @return The description/name of this mode
         */
        std::string getName() const override;

        /**
         * Returns the number of elements in a sample.<br>
         * The number of elements does not change during runtime.
         * @return
         * the number of elements in a sample
         */
        size_t sampleSize() const override;

        /**
         * calculated I2C address: 0 = GND, 1 = V+
         **/
        static constexpr uint8_t getAddress(uint8_t addr0, uint8_t addr1) {
            /* The address is controlled by the A0 and A1 inputs on the INA219:
             *
             * Calculated address: b100ABCD0
             * A0 controls C and D: GND = 00, V+ = 01, SDA = 10, SCL = 11
             * A1 controls A and B: GND = 00, V+ = 01, SDA = 10, SCL = 11
             *
             * E.g. if A0 is tied to ground and A1 is tied to V+,
             * the resulting address is b1000100 = 0x44
             *
             * SDA and SCL options aren't implemented.
             */
            return DEFAULT_ADDRESS | (addr0 != 0 ? 0x02 : 0x00) | (addr1 != 0 ? 0x08 : 0x00);
        }

    private:
        /**
         * Measuring the current in mA, the voltage in V
         */
        class CombinedMode : public SensorMode {
        private:
            CurrentSensorINA226 *m_sensor;
        public:
            explicit CombinedMode(CurrentSensorINA226 *sensor) : m_sensor(sensor) {
            }

            std::string getName() const override {
                return "Combined";
            }

            size_t sampleSize() const override {
                return 2;
            }

            void fetchSample(gsl::span<float> sample) override;
        };

        /**
         * Measuring the consumed power in mW
         */
        class PowerMode : public SensorMode {
        private:
            CurrentSensorINA226 *m_sensor;
        public:
            explicit PowerMode(CurrentSensorINA226 *sensor) : m_sensor(sensor) {
            }

            std::string getName() const override {
                return "Power";
            }

            size_t sampleSize() const override {
                return 1;
            }

            void fetchSample(gsl::span<float> sample) override;

        };

        /**
         * Measuring the shunt voltage in mV
         */
        class ShuntVoltageMode : public SensorMode {
        private:
            CurrentSensorINA226 *m_sensor;
        public:
            explicit ShuntVoltageMode(CurrentSensorINA226 *sensor) : m_sensor(sensor) {
            }

            std::string getName() const override {
                return "Shunt Voltage";
            }

            size_t sampleSize() const override {
                return 2;
            }

            void fetchSample(gsl::span<float> sample) override;
        };

    };

}