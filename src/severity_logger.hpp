/*
	liblogcpp: A simple, but highly customizable and intuitive LGPL library for logging with C++.
	Copyright (C) 2015 Sebastian Lau

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

/** File Version: 0.0.3-1 **/


#pragma once

#include "severity_log.hpp"
#include "severity.hpp"


namespace logcpp {


class severity_logger
	:	public severity_log< severity_level, severity_name, max_name_length >
{
public:


	/*
	 * Creates severity_logger logging to std::cout
	 */
	explicit severity_logger( severity_level max_severity = normal )
		:	severity_log< severity_level, severity_name, max_name_length >( max_severity )
	{
		this->current_severity = normal;
	}
	/*
	 * Creates severity_logger logging to stream
	 */
	explicit severity_logger( std::streambuf* stream, severity_level max_severity = normal )
		:	severity_log< severity_level, severity_name, max_name_length >( max_severity, stream)
	{
		this->current_severity = normal;
	}
	severity_logger( const severity_logger& ) = delete;
};

#define SCOPE_SEVERITY(lvl_) logcpp::severity_log< logcpp::severity_level, logcpp::severity_name >::severity_scope(lvl_, SCOPE)

} // namespace logcpp


#define CRITICAL SCOPE_SEVERITY(logcpp::critical)
#define DEBUG SCOPE_SEVERITY(logcpp::debug)

