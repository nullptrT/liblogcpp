/**
 * @file severity.hpp
 * @brief The default severities that are used in LibLogC++
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: A simple, intuitive and highly customizable LGPL library for logging with C++.
	Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
	Copyright (C) 2015-2016 Sebastian Lau <lauseb644@gmail.com>

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/


#pragma once

#include <string>
#include <array>


namespace logcpp {

/**
 * @brief The default severities that are used in LibLogC++
 * @note In all cases, the value 
 * @note - 0 defaults to off
 * @note - 1 defaults to critical
 * @note
 * @note The higher the enum value, the less critical is this severity
 */
enum severity_level {
	off,
	critical,
	error,
	warning,
	normal,
	verbose,
	debug
};

/**
 * @brief The names of severity_level as string array
 */
const std::array < std::string, 7 > names =
{
	"off",
	"critical",
	"error",
	"warning",
	"normal",
	"verbose",
	"debug"
};


/**
 * @return The name for severity_level as string
 * @param lvl A severity_level to get as string
 */
inline const std::string severity_name(severity_level lvl) {
	if( static_cast< std::size_t >(lvl) < names.size() ) {
		return names[lvl];
	} else {
		return names.back();
	}
}

/**
 * @return The amount of characters of the longest name of all severity_level
 */
inline const uint max_name_length() { return 8; }

} // namespace logcpp

