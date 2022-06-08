/*
 * I2CSensor.cpp
 */

#include <memory>
#include <thread>
#include <gsl/algorithm>
#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/sensor/I2CSensor.h>

namespace ev3lib::hardware::sensor {

    I2CSensor::I2CSensor(std::unique_ptr<ports::I2CPort> port)
            : I2CSensor(std::move(port), DEFAULT_I2C_ADDRESS) {

    }

    I2CSensor::I2CSensor(std::unique_ptr<ports::I2CPort> port, uint8_t address)
            : I2CSensor(std::move(port), address, ports::SensorType::LOWSPEED) {

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
    I2CSensor::I2CSensor(std::unique_ptr<ports::I2CPort> port, uint8_t address, ports::SensorType type)
            : m_port(std::move(port)), m_address(address) {

        if ((address & 1) != 0)
            throw std::invalid_argument("Bad address format: " + std::to_string(address));


        if (!m_port->setType(type)) {
            throw std::logic_error("Invalid sensor mode: " + std::to_string(static_cast<int>(type)));
        }
    }

    /**
     * Executes an I2C read transaction and waits for the result.
     *
     * @param reg I2C register, e.g 0x41
     * @param readBuf Buffer to return data
     */
    void I2CSensor::getData(uint8_t reg, gsl::span<uint8_t> readBuf) {
        std::lock_guard<std::mutex> guard(m_lock);

        uint8_t buf[1]{reg};

        execute(gsl::make_span(buf), readBuf);
    }

    /**
     *  Executes an I2C write transaction.
     *
     * @param register I2C register, e.g 0x42
     * @param writeBuf Buffer containing data to send
     */
    void I2CSensor::sendData(uint8_t reg, gsl::span<const uint8_t> writeBuf) {
        std::lock_guard<std::mutex> guard(m_lock);

        if (writeBuf.size() > detail::lms2012::IIC_DATA_LENGTH)
            throw std::invalid_argument("Invalid buffer length " + std::to_string(writeBuf.size()));

        uint8_t buf[detail::lms2012::IIC_DATA_LENGTH + 1];

        buf[0] = reg;

        if (!writeBuf.empty()) {
            gsl::copy(writeBuf, gsl::make_span(buf + 1, detail::lms2012::IIC_DATA_LENGTH));
        }

        execute(gsl::make_span(buf, writeBuf.size() + 1), gsl::span<uint8_t>());
    }

    /**
     * Executes I2C transaction with retry in case of error
     *
     * @param writeBuf input buffer
     * @param readBuf output buffer
     */
    void I2CSensor::execute(gsl::span<const uint8_t> writeBuf, gsl::span<uint8_t> readBuf) {
        int counter = m_retryCount;
        for (;;) {
            try {
                m_port->i2cTransaction(m_address, writeBuf, readBuf);
                return;
            }
            catch (const iic_error &e) {
                if (--counter == 0) {
                    throw;
                }
                std::this_thread::yield();
            }
        }
    }

    /**
     *  Executes an I2C write transaction.
     *
     * @param register I2C register, e.g 0x42
     * @param value single byte to send
     */
    void I2CSensor::sendData(uint8_t reg, uint8_t value) {
        std::lock_guard<std::mutex> guard(m_lock);

        uint8_t buf[2]{reg, value};

        execute(gsl::make_span(buf), gsl::span<uint8_t>());
    }

    /**
     * Read a string from the device.
     * This functions reads the specified number of bytes
     * and returns the characters before the zero termination byte.
     *
     * @param reg
     * @param len maximum length of the string, including the zero termination byte
     * @return the string containing the characters before the zero termination byte
     */
    std::string I2CSensor::fetchString(uint8_t reg, size_t len) {
        uint8_t buf[detail::lms2012::IIC_DATA_LENGTH];

        try {
            getData(reg, gsl::make_span(buf));
            return std::string{reinterpret_cast<char *>(buf), len};
        }
        catch (const std::exception &e) {
            return std::string{};
        }
    }
}
