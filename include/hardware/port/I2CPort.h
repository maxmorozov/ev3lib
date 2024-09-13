#pragma once

#include <span>
#include <utils/utilities.h>
#include <hardware/detail/lms2012/ev3_types.h>
#include <hardware/port/SensorType.h>

namespace ev3lib::hardware::port {

    /**
     * Abstraction for a port that supports I2C sensors.
     */
    struct I2CPort: utils::destructible {
        /** Maximum read/write request length */
        static constexpr int MAX_IO = detail::lms2012::IIC_DATA_LENGTH;

        /**
         * Set the operating type for the attached sensor. Normally type setting is
         * only used with legacy sensors and for i2c devices (to set the speed and
         * operating voltage). It is not normally used with EV3 sensors.
         * @param type
         * @return true if type accepted
         */
        [[nodiscard]]
        virtual bool setType(SensorType type) = 0;

        /**
         * High level i2c interface. Perform a complete i2c transaction and return
         * the results. Writes the specified data to the device and then reads the
         * requested bytes from it.
         *
         * @param deviceAddress The I2C device address.
         * @param writeBuf The buffer containing data to be written to the device.
         * @param readBuf The buffer to use for the transaction results
         */
        virtual void i2cTransaction(uint8_t deviceAddress, std::span<const uint8_t> writeBuf, std::span<uint8_t> readBuf) = 0;

    };

}
