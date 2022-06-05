#pragma once

#include <memory>
#include <mutex>
#include <hardware/detail/SensorsManager.h>
#include <hardware/sensor/MultiModeSensor.h>

namespace ev3lib::hardware {

    class I2CSensor {
    private:
        /**
         * Register number of sensor version string, as defined by standard Lego I2C register layout.
         * @see #getVersion()
         */
        static constexpr uint8_t REG_VERSION = 0x00;

        /**
         * Register number of sensor vendor ID, as defined by standard Lego I2C register layout.
         * @see #getVendorID()
         */
        static constexpr uint8_t REG_VENDOR_ID = 0x08;
        /**
         * Register number of sensor product ID, as defined by standard Lego I2C register layout.
         * @see #getProductID()
         */
        static constexpr uint8_t REG_PRODUCT_ID = 0x10;

        static constexpr size_t DEFAULT_I2C_ADDRESS = 0x02;

        std::mutex m_lock;
        std::unique_ptr<ports::I2CPort> m_port;
        uint8_t m_address;
        int m_retryCount = 3;

        /**
         * Executes I2C transaction with retry in case of error
         *
         * @param writeBuf input buffer
         * @param readBuf output buffer
         */
        void execute(gsl::span<const uint8_t> writeBuf, gsl::span<uint8_t> readBuf);

    protected:
        /**
         * Read a string from the device.
         * This functions reads the specified number of bytes
         * and returns the characters before the zero termination byte.
         *
         * @param reg
         * @param len maximum length of the string, including the zero termination byte
         * @return the string containing the characters before the zero termination byte
         */
        std::string fetchString(uint8_t reg, size_t len);

    public:
        I2CSensor(std::unique_ptr<ports::I2CPort> port);

        I2CSensor(std::unique_ptr<ports::I2CPort> port, uint8_t address);

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
        I2CSensor(std::unique_ptr<ports::I2CPort> port, uint8_t address, ports::SensorType type);

        int getRetryCount() const { return m_retryCount; }

        void setRetryCount(int value);

        /**
         * Return the the I2C address of the sensor.
         * The sensor uses the address for writing/reading.
         * @return the I2C address.
         */
        uint8_t getAddress() const {
            return m_address;
        }

        /**
         * Executes an I2C read transaction and waits for the result.
         *
         * @param reg I2C register, e.g 0x41
         * @param readBuf Buffer to return data
         */
        void getData(uint8_t reg, gsl::span<uint8_t> readBuf);

        /**
         *  Executes an I2C write transaction.
         *
         * @param register I2C register, e.g 0x42
         * @param writeBuf Buffer containing data to send
         */
        void sendData(uint8_t reg, gsl::span<const uint8_t> writeBuf);

        /**
         *  Executes an I2C write transaction.
         *
         * @param register I2C register, e.g 0x42
         * @param value single byte to send
         */
        void sendData(uint8_t reg, uint8_t value);

        /**
         * Read the sensor's version string.
         * This method reads up to 8 bytes
         * and returns the characters before the zero termination byte.
         * Examples: "V1.0", ...
         *
         * @return version number
         */
        std::string getVersion() {
            return fetchString(REG_VERSION, 8);
        }

        /**
         * Read the sensor's vendor identifier.
         * This method reads up to 8 bytes
         * and returns the characters before the zero termination byte.
         * Examples: "LEGO", "HiTechnc", ...
         *
         * @return vendor identifier
         */
        std::string getVendorID() {
            return fetchString(REG_VENDOR_ID, 8);
        }

        /**
         * Read the sensor's product identifier.
         * This method reads up to 8 bytes
         * and returns the characters before the zero termination byte.
         * Examples: "Sonar", ...
         *
         * @return product identifier
         */
        std::string getProductID() {
            return fetchString(REG_PRODUCT_ID, 8);
        }

    };

}
