cmake_minimum_required(VERSION 3.8)
project(ev3lib)

set(SOURCE_FILES
        include/exceptions/EV3HardwareExceptions.h
        include/hardware/detail/lejos/motor_data.h
        include/hardware/detail/lejos/uart_data.h
        include/hardware/detail/lms2012/ev3_constants.h
        include/hardware/detail/lms2012/ev3_types.h
        include/hardware/detail/ports/AnalogPort.h
        include/hardware/detail/ports/MultiModePort.h
        include/hardware/detail/ports/UartPort.h
        include/hardware/detail/BatteryManager.h
        include/hardware/detail/device_traits.h
        include/hardware/detail/ev3_brick.h
        include/hardware/detail/ev3_device.h
        include/hardware/detail/handle.h
        include/hardware/detail/MotorManager.h
        include/hardware/detail/Power.h
        include/hardware/detail/SensorsManager.h
        include/hardware/detail/UIManager.h
        include/hardware/sensor/eeprom/AccelEepromWriter.h
        include/hardware/sensor/eeprom/GyroEepromWriter.h
        include/hardware/sensor/eeprom/MagEepromWriter.h
        include/hardware/sensor/scale/AccelScaleSelector.h
        include/hardware/sensor/scale/GyroScaleSelector.h
        include/hardware/sensor/scale/MagScaleSelector.h
        include/hardware/sensor/AnalogSensor.h
        include/hardware/sensor/HiTechnicGyro.h
        include/hardware/sensor/ImuLsm6ds3.h
        include/hardware/sensor/MultiModeSensor.h
        include/hardware/sensor/NXTLightSensor.h
        include/hardware/sensor/SensorMode.h
        include/hardware/sensor/SensorModes.h
        include/hardware/sensor/UartSensor.h
        include/hardware/Battery.h
        include/hardware/Brick.h
        include/hardware/Button.h
        include/hardware/Tachometer.h
        include/hardware/UnregulatedMotor.h
        include/robotics/SampleProvider.h
        include/utils/utilities.h
        include/utils/str_const.h
        src/hardware/detail/AnalogSensorHelpers.cpp
        src/hardware/detail/AnalogSensorHelpers.h
        src/hardware/detail/DetachSubscriber.h
        src/hardware/detail/ev3_brick.cpp
        src/hardware/detail/EV3AnalogPort.cpp
        src/hardware/detail/EV3AnalogPort.h
        src/hardware/detail/EV3Battery.cpp
        src/hardware/detail/EV3Battery.h
        src/hardware/detail/EV3DeviceManager.cpp
        src/hardware/detail/EV3DeviceManager.h
        src/hardware/detail/EV3MotorPort.cpp
        src/hardware/detail/EV3MotorPort.h
        src/hardware/detail/EV3SensorConstants.h
        src/hardware/detail/EV3SensorType.h
        src/hardware/detail/EV3UartPort.cpp
        src/hardware/detail/EV3UartPort.h
        src/hardware/detail/handle.cpp
        src/hardware/sensor/AnalogSensor.cpp
        src/hardware/sensor/HiTechnicGyro.cpp
        src/hardware/sensor/ImuLsm6ds3.cpp
        src/hardware/sensor/MultiModeSensor.cpp
        src/hardware/sensor/NXTLightSensor.cpp
        src/hardware/sensor/UartSensor.cpp
        src/hardware/Battery.cpp
        src/hardware/Brick.cpp
        src/hardware/Button.cpp
        src/hardware/UnregulatedMotor.cpp)

include_directories(include)

add_library(ev3lib STATIC ${SOURCE_FILES})

set_target_properties(ev3lib PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
