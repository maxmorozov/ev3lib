#pragma once

#include <utilities.h>
#include <vector>
#include <string>

#include <robotics/SampleProvider.h>

namespace ev3lib {
namespace hardware {

	struct SensorMode : public robotics::SampleProvider
	{
		/**
		 * return a string description of this sensor mode
		 * @return The description/name of this mode
		 */
		virtual std::string getName() const = 0;

		// TODO: Return additional mode information

	};

}}
