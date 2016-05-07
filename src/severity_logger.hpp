/**
 * @file severity_logger.hpp
 * @brief A severity logger that can be used instantly
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: A intuitive and highly customizable LGPL library for logging with C++.
	Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
	Copyright (C) 2015-2016 Sebastian Lau <lauseb644@gmail.com>

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

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

#include "config.hpp"

#include "severity_log.hpp"
#include "severity_default.hpp"


namespace logcpp {

/**
 * @brief A severity logger that can be used instantly
 */
class severity_logger
	:	public severity_log< default_severity_levels >
{
public:
	/**
	 * @brief Creates severity_logger logging to std::cout
	 * @param max_severity The maximum severity level for this logger
	 */
	severity_logger( default_severity_levels max_severity = normal );

	/**
	 * @brief Creates severity_logger logging to a specific streambuf
	 * @param stream A pointer to some std::streambuf where all content is logged to.
	 * @param max_severity The maximum severity level for this logger
	 */
	explicit severity_logger( std::streambuf* stream, default_severity_levels max_severity = normal );

    severity_logger( const severity_logger& ) = delete;
};


/**
 * @brief Template specialization for endl and default severities
 */
template severity_log< default_severity_levels >& endl(severity_log< default_severity_levels >&);
template severity_logger& endl(severity_logger&);

/**
 * @brief Template specialization for endrec and default severities
 */
template severity_log< default_severity_levels >& endrec(severity_log< default_severity_levels >&);
template severity_logger& endrec(severity_logger&);

} // namespace logcpp


/**
 * @def SCOPE_SEVERITY(lvl_)
 * @brief Insert a severity with the current scope into the severity_logger
 * @param lvl_ The severity level to be inserted into the severity_logger
 */
#define SCOPE_SEVERITY(lvl_) logcpp::severity_log< logcpp::default_severity_levels >::severity_scope(lvl_, SCOPE)


/**
 * @def CRITICAL
 * @brief Insert a critical scope into the log stream that may call the critical function of severity_log
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define CRITICAL logcpp::col_red << logcpp::sty_bold << SCOPE_SEVERITY(logcpp::critical) << logcpp::ctl_reset_all
#else
#define CRITICAL SCOPE_SEVERITY(logcpp::critical)
#endif

/**
 * @def ERROR
 * @brief Insert a error into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define ERROR logcpp::col_red << logcpp::error << logcpp::ctl_reset_col
#else
#define ERROR logcpp::error
#endif

/**
 * @def WARNING
 * @brief Insert a warning into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define WARNING logcpp::col_yellow << logcpp::warning << logcpp::ctl_reset_col
#else
#define WARNING logcpp::warning
#endif

/**
 * @def VERBOSE
 * @brief Insert a verbose into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define VERBOSE logcpp::col_cyan << logcpp::verbose << logcpp::ctl_reset_col
#else
#define VERBOSE logcpp::verbose
#endif

/**
 * @def VERBOSE2
 * @brief Insert a verbose2 into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define VERBOSE2 logcpp::col_blue << logcpp::verbose2 << logcpp::ctl_reset_col
#else
#define VERBOSE2 logcpp::verbose2
#endif

/**
 * @def DEBUG
 * @brief Insert a debug severity into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define DEBUG logcpp::col_white << logcpp::debug << logcpp::ctl_reset_col
#else
#define DEBUG logcpp::debug
#endif

/**
 * @def DEBUG2
 * @brief Insert a debug2 scope into the log stream
 */
#ifdef LOGCPP_ENABLE_COLOR_SUPPORT
#define DEBUG2 logcpp::col_white << SCOPE_SEVERITY(logcpp::debug2) << logcpp::ctl_reset_col
#else
#define DEBUG2 logcpp::debug2
#endif
