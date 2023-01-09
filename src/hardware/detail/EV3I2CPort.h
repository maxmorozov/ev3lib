#pragma once

#include <hardware/port/I2CPort.h>
#include <hardware/detail/lejos/port_data.h>
#include "EV3DeviceManager.h"

namespace ev3lib::hardware::detail {

    /**
        Provide access to EV3 I2C sensors.<BR>
        NOTE: The EV3 iic kernel module provides the capability to make an i2c sensor
        have a similar interface to that used for uart based sensors. In particular it
        provides a mechanism to have the kernel poll the sensor. However this mode seems
        to be of limited use because most i2c sensors provide multiple data values etc.
        Because of this we only implement the basic i2c interface.
     */
    class EV3I2CPort : public port::I2CPort, public DetachSubscriber {
    private:
        EV3DeviceManager* m_manager;
        size_t m_port;

        void connect();
        void disconnect();

        bool setPinMode(AnalogMode mode);

        EV3Device<device_type::i2c_sensor>& getDevice() {
            if (m_manager == nullptr) {
                throw device_error("Device manager is detached");
            }
            return m_manager->m_i2cDevice;
        }

    protected:
        static constexpr uint32_t IIC_CONNECT = lejos::IIC_CONNECT;
        static constexpr uint32_t IIC_DISCONNECT = lejos::IIC_DISCONNECT;
        static constexpr uint32_t IIC_IO = lejos::IIC_IO;

        /** Maximum read/write request length */
        static constexpr int MAX_IO = lms2012::IIC_DATA_LENGTH;

        static constexpr int IO_TIMEOUT = 2000;

        enum class I2CSpeed : uint8_t {
            SPEED_10KHZ = 0,
            SPEED_100KHZ = 1
        };

        I2CSpeed speed = I2CSpeed::SPEED_10KHZ;

    public:
        EV3I2CPort(EV3DeviceManager* manager, size_t port);
        ~EV3I2CPort() override;

        void detach() override;

        /**
         * Set the operating type for the attached sensor. Normally type setting is
         * only used with legacy sensors and for i2c devices (to set the speed and
         * operating voltage). It is not normally used with EV3 sensors.
         * @param type
         * @return true if type accepted
         */
        bool setType(port::SensorType type) override;

        /**
         * High level i2c interface. Perform a complete i2c transaction and return
         * the results. Writes the specified data to the device and then reads the
         * requested bytes from it.
         *
         * @param deviceAddress The I2C device address.
         * @param writeBuf The buffer containing data to be written to the device.
         * @param readBuf The buffer to use for the transaction results
         */
        void i2cTransaction(uint8_t deviceAddress, std::span<const uint8_t> writeBuf, std::span<uint8_t> readBuf) override;
    };

}

