#include <chrono>
#include <thread>
#include <vector>

#include <exceptions/EV3HardwareExceptions.h>

#include "EV3UartPort.h"
#include "EV3SensorConstants.h"
#include "EV3SensorType.h"

namespace ev3lib {
namespace hardware {
namespace detail {

namespace {
	typedef BufferCommand<unsigned char, 1> Command1;
	typedef BufferCommand<unsigned char, 2> Command2;
	typedef BufferCommand<unsigned char, 3> Command3;
}


EV3UartPort::EV3UartPort(EV3DeviceManager* manager, size_t port)
	: m_manager(manager), m_port(port)
{
    initializeSensor(m_currentMode);
}

EV3UartPort::~EV3UartPort()
{
	disconnect();
    if (m_manager)
    	m_manager->disconnect(m_port, PortType::Sensor);
}

void EV3UartPort::detach() 
{
	m_manager = nullptr;
}

/**
 * Get the current operating mode of the sensor
 * @return the current mode
 */
size_t EV3UartPort::getMode() const
{
	return m_currentMode;
}

/**
 * Set the current operating mode for the sensor attached to the port.
 * @param mode the new mode
 * @return true if the mode has been accepted
 */
bool EV3UartPort::setMode(size_t mode)
{
    // are we initialized ?
    if (m_modeInfo.empty())
        return initializeSensor(mode);
    if (mode >= m_modeInfo.size())
        return false;
    setOperatingMode(mode);
    int status = waitNonZeroStatus(TIMEOUT);
    if ((status & lms2012::UART_DATA_READY) != 0 && (status & lms2012::UART_PORT_CHANGED) == 0) {
        m_currentMode = mode;
        return true;
    } else {
        // Sensor may have reset try and initialise it in the new mode.
        return initializeSensor(mode);
    }
}

/**
 * Returns numner of supported modes
 *
 * @return number of available modes
 */
size_t EV3UartPort::getModeCount() const
{
	return m_modeInfo.size();
}

const uint8_t* EV3UartPort::getData() const {
	auto uartData = m_manager->m_uartDevice.getSensorData();
#ifndef DISABLE_FAST_DATALOG_BUFFER
	return (uint8_t*)uartData->Raw[m_port][uartData->Actual[m_port]];
#else
	return (uint8_t*)uartData->Raw[m_port];
#endif
}

/**
 * read a number of bytes from the device
 * @param buffer byte array to accept the data
 * @param offset offset (in bytes) at which to store the data
 * @param len number of bytes to read
 */
void EV3UartPort::read(uint8_t* buffer, size_t offset, size_t len)
{
    checkSensor();

    const uint8_t* data = getData() + offset;
    std::copy(data, data + len, buffer);
}

/**
 * Write bytes to the sensor
 * @param buffer bytes to be written
 * @param offset offset to the start of the write
 * @param len length of the write
 * @return number of bytes written
 */
int EV3UartPort::write(const uint8_t* buffer, size_t offset, size_t len)
{
    std::vector<uint8_t> command(len + 1);
    command[0] = (uint8_t) m_port;
    std::copy(buffer + offset, buffer + offset + len, command.begin() + 1);
	ssize_t ret = m_manager->m_uartDevice.sendCommand(&command[0], command.size());
    if (ret > 0) 
    	--ret;
    return ret;
}

/**
 * Get the string name of the specified mode.<p><p>
 * @param mode mode to lookup
 * @return String version of the mode name
 */
std::string EV3UartPort::getModeName(size_t mode) const
{
    if (mode < m_modeInfo.size()) {
        return (const char*)m_modeInfo[mode].Name;
    }
    else 
        return "Unknown";
}

/**
 * Connect to the device
 */
void EV3UartPort::connect()
{
	Command1 command;
	command[0] = m_port;
	m_manager->m_uartDevice.ioctl(lejos::UART_CONNECT, command.buffer());
}

/**
 * Disconnect to the device
 */
void EV3UartPort::disconnect()
{
	Command1 command;
	command[0] = m_port;
	m_manager->m_uartDevice.ioctl(lejos::UART_DISCONNECT, command.buffer());
}

/**
 * Attempt to initialize the sensor ready for use.
 * @param mode initial operating mode
 * @return -1 no uart, 0 failed to initialize, 1 sensor initialized
 */
int EV3UartPort::initSensor(size_t mode)
{
    int status;
    int retryCnt = 0;
    lms2012::UARTCTL uc = {0};
    // now try and configure as a UART
    setOperatingMode(mode);
    status = waitNonZeroStatus(TIMEOUT);
    if ((status & lejos::UART_PORT_ERROR) != 0)
		return -1;
    while((status & lms2012::UART_PORT_CHANGED) != 0 && retryCnt++ < INIT_RETRY)
    {
        // something change wait for it to become ready
        clearPortChanged(&uc);
        status = waitNonZeroStatus(TIMEOUT);
        if ((status & lms2012::UART_DATA_READY) != 0 && (status & lms2012::UART_PORT_CHANGED) == 0)
        {
            // device ready make sure it is now in the correct mode
            setOperatingMode(mode);
            status = waitNonZeroStatus(TIMEOUT);
        }
    }
    if ((status & lms2012::UART_DATA_READY) != 0 && (status & lms2012::UART_PORT_CHANGED) == 0)
        return 1;
    else
        return 0;
}


/**
 * Initialize the attached sensor and set it to the required operating mode.<br>
 * Note: This method is not normally needed as the sensor will be initialized
 * when it is opened. However it may be of use if the sensor needs to be reset
 * or in other cases.
 * @param mode target mode
 * @return true if ok false if error
 */
bool EV3UartPort::initializeSensor(size_t mode)
{
    connect();
    for(int i = 0; i < OPEN_RETRY; i++)
    {
        // initialize the sensor, if we have no mode data
        // then read it, otherwise use what we have
        int res = initSensor(mode);
        if (res < 0) 
			break;
        if (res > 0 && (!m_modeInfo.empty() || readModeInfo()))
        {
            m_currentMode = mode;
            return true;
        }
        resetSensor();
    }
    disconnect();
    return false;
}


/**
 * Reset the attached sensor. Following this the sensor must be initialized
 * before it can be used.
 */
void EV3UartPort::resetSensor()
{
    reset();
    waitZeroStatus(TIMEOUT);
}

/**
 * reset the port and device
 */
void EV3UartPort::reset()
{
    // Force the device to reset
    disconnect();
    connect();
}


/**
 * Read the mode information from the port. return true 
 * @return
 */
bool EV3UartPort::readModeInfo()
{
	std::vector<lms2012::TYPES> modeInfo;
    for(size_t i = 0; i < lms2012::MAX_DEVICE_MODES; ++i)
    {
    	lms2012::UARTCTL uc = {0};
        if (getModeInfo(i, &uc))
        {
            clearModeCache(i, &uc);
            modeInfo.push_back(uc.TypeData);
        } else {
            break;
        }
    }
    m_modeInfo.swap(modeInfo);
    return !m_modeInfo.empty();
}


/**
 * Wait for the port status to become non zero, or for the operation to timeout
 * @param timeout timeout period in ms
 * @return port status or 0 if the operation timed out
 */
int EV3UartPort::waitNonZeroStatus(int timeout)
{
    std::chrono::milliseconds delay(TIMEOUT_DELTA);

    int cnt = timeout / TIMEOUT_DELTA;
    int8_t status = getStatus();
    while (status == 0 && cnt-- > 0)
    {
    	std::this_thread::sleep_for(delay);
        status = getStatus();
    }
    return status;       
}

/**
 * Wait for the port status to become zero
 * @param timeout timeout period in ms
 * @return zero if successful or the current status if timed out
 */
int EV3UartPort::waitZeroStatus(int timeout)
{
	std::chrono::milliseconds delay(TIMEOUT_DELTA);

    int cnt = timeout / TIMEOUT_DELTA;
    int8_t status = getStatus();
    while (status != 0 && cnt-- > 0)
    {
    	std::this_thread::sleep_for(delay);
        status = getStatus();
    }
    return status;       
}


/**
 * return the current status of the port
 * @return status
 */
int8_t EV3UartPort::getStatus() const
{
    return m_manager->m_uartDevice.getSensorData()->Status[m_port];
}

/**
 * Set the current operating mode
 * @param mode
 */
void EV3UartPort::setOperatingMode(size_t mode)
{
	Command2 command;
	command[0] = m_port;
	command[1] = mode;
	m_manager->m_uartDevice.ioctl(lejos::UART_SETMODE, command.buffer());
}

/**
 * Read the mode information for the specified operating mode.
 * @param mode mode number to read
 * @param uc control structure to read the data into
 * @return
 */
bool EV3UartPort::getModeInfo(size_t mode, lms2012::UARTCTL* uc)
{
    uc->Port = (int8_t)m_port;
    uc->Mode = (int8_t)mode;
	m_manager->m_uartDevice.ioctl(lms2012::UART_READ_MODE_INFO, uc);
    return uc->TypeData.Name[0] != 0;
}
    
/**
 * Clear the flag that indicates the mode info has been cached. This
 * allows us to read the same information again later without having to
 * reset the device.
 * @param mode mode number to read
 * @param uc control structure to read the data into
 * @return
 */
void EV3UartPort::clearModeCache(size_t mode, lms2012::UARTCTL* uc)
{
    uc->Port = (int8_t)m_port;
    uc->Mode = (int8_t)mode;
	m_manager->m_uartDevice.ioctl(lms2012::UART_NACK_MODE_INFO, uc);
}

/**
 * Clear the port changed flag for the current port.
 */
void EV3UartPort::clearPortChanged(lms2012::UARTCTL* uc)
{
    //Is it necessary? It seems the last line is enough
    uc->Port = (int8_t)m_port;
	m_manager->m_uartDevice.ioctl(lms2012::UART_CLEAR_CHANGED, uc);

    m_manager->m_uartDevice.getSensorData()->Status[m_port] &= ~lms2012::UART_PORT_CHANGED;
}

/**
 * Check the sensor status, and if possible recover any from any error.
 * If everything fails throw an exception
 */
void EV3UartPort::checkSensor()
{
    if ((getStatus() & lms2012::UART_PORT_CHANGED) != 0)
    {
        // try and reinitialize it
        if (!initializeSensor(getMode()))
            throw device_error("Sensor changed. Unable to reset");
            
    }
}

} /* namespace detail */
} /* namespace hardware */
} /* namespace ev3lib */
