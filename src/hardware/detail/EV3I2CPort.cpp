#include <exceptions/EV3HardwareExceptions.h>
#include <hardware/detail/lejos/port_data.h>
#include <utils/algorithm.h>
#include <utils/type_utils.h>
#include "EV3I2CPort.h"


namespace ev3lib::hardware::detail {

    EV3I2CPort::EV3I2CPort(EV3DeviceManager* manager, port_type port)
            : m_manager(manager), m_port(port) {
        //Try to connect the sensor in the constructor to avoid
        //destructor calling if another sensor is already attached to this port
        manager->connectSensor(port, this);
    }

    EV3I2CPort::~EV3I2CPort() {
        close();
    }

    void EV3I2CPort::close() {
        if (m_manager != nullptr) {
            disconnect();
            m_manager->disconnect(m_port, PortType::Sensor);
        }
    }

    void EV3I2CPort::connect() {
        lejos::DEVCTL command;
        command.Port = m_port;
        getDevice().ioctl(lejos::IIC_CONNECT, &command);
    }

    void EV3I2CPort::disconnect() {
        lejos::DEVCTL command;
        command.Port = m_port;
        getDevice().ioctl(lejos::IIC_DISCONNECT, &command);
    }

    void EV3I2CPort::detach() {
        close();
        m_manager = nullptr;
    }

    /**
     * Set the operating type for the attached sensor. Normally type setting is
     * only used with legacy sensors and for i2c devices (to set the speed and
     * operating voltage). It is not normally used with EV3 sensors.
     * @param type
     * @return true if type accepted
     */
    bool EV3I2CPort::setType(port::SensorType type) {
        speed = I2CSpeed::SPEED_10KHZ;
        switch (type) {
            case port::SensorType::HIGHSPEED:
                speed = I2CSpeed::SPEED_100KHZ;
                [[fallthrough]];
            case port::SensorType::LOWSPEED:
                setPinMode(AnalogMode::Set | AnalogMode::Pin5);
                break;
            case port::SensorType::HIGHSPEED_9V:
                speed = I2CSpeed::SPEED_100KHZ;
                [[fallthrough]];
            case port::SensorType::LOWSPEED_9V:
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
    void EV3I2CPort::i2cTransaction(uint8_t deviceAddress, std::span<const uint8_t> writeBuf, std::span<uint8_t> readBuf) {
        uint8_t command[MAX_IO + 5];

        if (writeBuf.size() > MAX_IO) {
            throw std::invalid_argument("Write buffer overflow. Buffer size " + std::to_string(writeBuf.size()));
        }
        if (readBuf.size() > MAX_IO) {
            throw std::invalid_argument("Read buffer overflow. Buffer size " + std::to_string(readBuf.size()));
        }

        command[0] = m_port;
        command[1] = utils::to_underlying(speed);
        command[2] = readBuf.size();
        command[3] = writeBuf.size();
        command[4] = deviceAddress >> 1;

        if (!writeBuf.empty()) {
            utils::copy(writeBuf, std::span(command + 5, MAX_IO));
        }

        getDevice().ioctl(lejos::IIC_IO, command);

        int result = command[1];
        switch (result) {
            case lejos::STATUS_OK:
                if (!readBuf.empty()) {
                    utils::copy(std::span(command + 5, readBuf.size()), readBuf);
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

