#pragma once

#include <vector>
#include <hardware/sensor/SensorModes.h>

namespace ev3lib::hardware::sensor {

    class MultiModeSensor: public SensorModes {
    protected:
        //Mode description
        struct ModeInfo {
            std::string name;
            size_t sampleSize;
        };

        std::vector<ModeInfo> m_modes;
        size_t m_currentMode = 0;

        bool isValid(size_t mode) const;

        virtual void switchMode(size_t mode) = 0;

    public:
        explicit MultiModeSensor(std::vector<ModeInfo> modes, size_t mode);

        MultiModeSensor(MultiModeSensor&& other) noexcept;

        MultiModeSensor& operator=(MultiModeSensor&&) = delete;

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
        size_t getCurrentMode() const override;

        /**
         * Gets the number of supported modes
         * @return the number of supported modes
         */
        size_t getModeCount() const override;

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
    };


} /* namespace ev3lib::hardware */
