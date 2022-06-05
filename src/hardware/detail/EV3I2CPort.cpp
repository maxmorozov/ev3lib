#include <gsl/algorithm>
#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/detail/lejos/port_data.h>
#include "EV3I2CPort.h"


namespace ev3lib::hardware::detail {

    EV3I2CPort::EV3I2CPort(EV3DeviceManager *manager, size_t port)
            : m_manager(manager), m_port(port) {
    }

    EV3I2CPort::~EV3I2CPort() {
        disconnect();
        if (m_manager != nullptr)
            m_manager->disconnect(m_port, PortType::Sensor);

    }

    void EV3I2CPort::connect() {
        uint8_t command[1];
        command[0] = m_port;
        getDevice().ioctl(lejos::IIC_CONNECT, command);
    }

    void EV3I2CPort::disconnect() {
        uint8_t command[1];
        command[0] = m_port;
        getDevice().ioctl(lejos::IIC_DISCONNECT, command);
    }

    void EV3I2CPort::detach() {
        m_manager = nullptr;
    }

    /**
     * Set the operating type for the attached sensor. Normally type setting is
     * only used with legacy sensors and for i2c devices (to set the speed and
     * operating voltage). It is not normally used with EV3 sensors.
     * @param type
     * @return true if type accepted
     */
    bool EV3I2CPort::setType(ports::SensorType type) {
        speed = I2CSpeed::SPEED_10KHZ;
        switch (type) {
            case ports::SensorType::HIGHSPEED:
                speed = I2CSpeed::SPEED_100KHZ;
                [[fallthrough]];
            case ports::SensorType::LOWSPEED:
                setPinMode(AnalogMode::Set | AnalogMode::Pin5);
                break;
            case ports::SensorType::HIGHSPEED_9V:
                speed = I2CSpeed::SPEED_100KHZ;
                [[fallthrough]];
            case ports::SensorType::LOWSPEED_9V:
                setPinMode(AnalogMode::Set | AnalogMode::Pin1 | AnalogMode::Pin5);
                break;
            default:
                return false;
        }
        connect();
        return true;
    }


    /**
     * High level i2c interface. Perform a complete i2c transaction and return
     * the results. Writes the specified data to the device and then reads the
     * requested bytes from it.
     *
     * @param deviceAddress The I2C device address.
     * @param writeBuf The buffer containing data to be written to the device.
     * @param readBuf The buffer to use for the transaction results
     */
    void EV3I2CPort::i2cTransaction(uint8_t deviceAddress, gsl::span<const uint8_t> writeBuf, gsl::span<uint8_t> readBuf) {
        uint8_t command[MAX_IO + 5];

        if (writeBuf.size() > MAX_IO) {
            throw std::invalid_argument("Write buffer overflow. Buffer size " + std::to_string(writeBuf.size()));
        }

        command[0] = m_port;
        command[1] = (uint8_t) speed;
        command[2] = readBuf.size();
        command[3] = writeBuf.size();
        command[4] = deviceAddress >> 1;

        if (!writeBuf.empty()) {
            gsl::copy(readBuf, gsl::make_span(command + 5, MAX_IO));
        }

        getDevice().ioctl(lejos::IIC_IO, command);

        int result = (int) command[1];
        switch (result) {
            case lejos::STATUS_OK:
                if (!readBuf.empty()) {
                    gsl::copy(gsl::make_span(command + 5, readBuf.size()), readBuf);
                }
                break;
            case lejos::STATUS_FAIL:
                throw iic_error("I2C I/O error");
            case lejos::STATUS_BUSY:
                throw iic_error("I2C Bus busy");
            default:
                throw iic_error("I2C Unexpected error: " + std::to_string(result))
                        << error_code(result);
        }
    }

    bool EV3I2CPort::setPinMode(AnalogMode mode) {
        if (m_manager != nullptr) {
            m_manager->setPortMode(m_port, PortType::Sensor, mode);
            return true;
        } else {
            return false;
        }
    }

}

