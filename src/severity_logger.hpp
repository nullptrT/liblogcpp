/**
 * @file severity_logger.hpp
 * @brief A severity logger that can be used instantly
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: A simple, but highly customizable and intuitive LGPL library for logging with C++.
	Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
	Copyright (C) 2015 Sebastian Lau <lauseb644@gmail.com>

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

#include "severity_log.hpp"
#include "severity.hpp"


namespace logcpp {

/**
 * @brief A severity logger that can be used instantly
 */
class severity_logger
	:	public severity_log< severity_level, severity_name, max_name_length >
{
public:


	/**
	 * @brief Creates severity_logger logging to std::cout
	 * @param max_severity The maximum severity level for this logger
	 */
	explicit severity_logger( severity_level max_severity = normal )
		:	severity_log< severity_level, severity_name, max_name_length >( max_severity )
	{
		this->current_severity = normal;
	}
	/**
	 * @brief Creates severity_logger logging to a specific streambuf
	 * @param stream A pointer to some std::streambuf where all content is logged to.
	 * @param max_severity The maximum severity level for this logger
	 */
	explicit severity_logger( std::streambuf* stream, severity_level max_severity = normal )
		:	severity_log< severity_level, severity_name, max_name_length >( max_severity, stream)
	{
		this->current_severity = normal;
	}
	severity_logger( const severity_logger& ) = delete;
};

/**
 * @def SCOPE_SEVERITY(lvl_)
 * @brief Insert a severity with the current scope into the severity_logger
 * @param lvl_ The severity level to be inserted into the severity_logger
 */
#define SCOPE_SEVERITY(lvl_) logcpp::severity_log< logcpp::severity_level, logcpp::severity_name >::severity_scope(lvl_, SCOPE)

} // namespace logcpp

/**
 * @def CRITICAL
 * @brief Insert a critical scope into the log stream that may call the critical function of severity_log
 */
#define CRITICAL SCOPE_SEVERITY(logcpp::critical)
/**
 * @def DEBUG
 * @brief Insert a debug scope into the log stream
 */
#define DEBUG SCOPE_SEVERITY(logcpp::debug)

