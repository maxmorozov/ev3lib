#ifndef EV3UARTPORT_H_
#define EV3UARTPORT_H_

#include <vector>
#include <hardware/detail/ev3_device.h>
#include <hardware/detail/lejos/port_data.h>
#include "EV3DeviceManager.h"

namespace ev3lib::hardware::detail {

	class EV3UartPort: public port::UartPort, public DetachSubscriber {
	    static const int TIMEOUT_DELTA = 1;
	    static const int TIMEOUT = 4000;
	    static const int INIT_DELAY = 5;
	    static const int INIT_RETRY = 100;
	    static const int OPEN_RETRY = 5;

	private:
		EV3DeviceManager* m_manager;
		size_t m_port;

    	size_t m_currentMode = 0;
    	std::vector<lms2012::TYPES> m_modeInfo;

        const EV3InputDevice<device_type::uart_sensor>& getDevice() const {
            if (m_manager == nullptr) {
                throw device_error("Device manager is detached");
            }
            return m_manager->m_uartDevice;
        }

        EV3InputDevice<device_type::uart_sensor>& getDevice() {
            if (m_manager == nullptr) {
                throw device_error("Device manager is detached");
            }
            return m_manager->m_uartDevice;
        }

		/**
		 * return the current status of the port
		 * @return status
		 */
		int8_t getStatus() const;
		                
		/**
		 * Wait for the port status to become non zero, or for the operation to timeout
		 * @param timeout timeout period in ms
		 * @return port status or 0 if the operation timed out
		 */
		int waitNonZeroStatus(int timeout);

		/**
		 * Wait for the port status to become zero
		 * @param timeout timeout period in ms
		 * @return zero if successful or the current status if timed out
		 */
		int waitZeroStatus(int timeout);

		/**
		 * Initialise the attached sensor and set it to the required operating mode.<br>
		 * Note: This method is not normally needed as the sensor will be initialised
		 * when it is opened. However it may be of use if the sensor needs to be reset
		 * or in other cases.
		 * @param mode target mode
		 * @return true if ok false if error
		 */
		bool initializeSensor(size_t mode);

		/**
		 * Attempt to initialise the sensor ready for use.
		 * @param mode initial operating mode
		 * @return -1 no uart, 0 failed to initialise, 1 sensor initialised
		 */
		int initSensor(size_t mode);

		/**
		 * Read the mode information from the port. return true 
		 * @return
		 */
		bool readModeInfo();

		/**
		 * Set the current operating mode
		 * @param mode
		 */
		void setOperatingMode(size_t mode);

		/**
		 * Read the mode information for the specified operating mode.
		 * @param mode mode number to read
		 * @param uc control structure to read the data into
		 * @return
		 */
		bool getModeInfo(size_t mode, lms2012::UARTCTL* uc);

		/**
		 * Clear the flag that indicates the mode info has been cached. This
		 * allows us to read the same infomration again later without having to
		 * reset the device.
		 * @param mode mode number to read
		 * @param uc control structure to read the data into
		 * @return
		 */
		void clearModeCache(size_t mode, lms2012::UARTCTL* uc);

		/**
		 * Clear the port changed flag for the current port.
		 */
		void clearPortChanged(lms2012::UARTCTL* uc);

		/**
		 * Check the sensor status, and if possible recover any from any error.
		 * If everything fails throw an exception
		 */
		void checkSensor() ;

		/**
		 * reset the port and device
		 */
		void reset();

		const uint8_t* getData() const;

		void connect();

		void disconnect();


	public:
		EV3UartPort(EV3DeviceManager* manager, size_t port);
		~EV3UartPort() override;

		void detach() override;

		/**
		 * Reset the attached sensor. Following this the sensor must be initialized
		 * before it can be used.
		 */
		void resetSensor() override;

	    /**
	     * Get the current operating mode of the sensor
	     * @return the current mode
	     */
		size_t getMode() const override;

	    /**
	     * Set the current operating mode for the sensor attached to the port.
	     * @param mode the new mode
	     * @return true if the mode has been accepted
	     */
		bool setMode(size_t mode) override;

	    /**
	     * Returns number of supported modes
	     *
	     * @return number of available modes
	     */
		size_t getModeCount() const override;

	    /**
	     * read a number of bytes from the device
	     * @param buffer byte array to accept the data
	     * @param offset offset (in bytes) at which to store the data
	     */
		void read(std::span<uint8_t> buffer) override;

	    /**
	     * Write bytes to the sensor
	     * @param buffer bytes to be written
	     * @param offset offset to the start of the write
	     * @return number of bytes written
	     */
		ssize_t write(std::span<const uint8_t> buffer) override;

	    /**
	     * Get the string name of the specified mode.<p><p>
	     * @param mode mode to lookup
	     * @return String version of the mode name
	     */
		std::string getModeName(size_t mode) const override;
	};

} /* namespace ev3lib::hardware::detail */

#endif /* EV3UARTPORT_H_ */
