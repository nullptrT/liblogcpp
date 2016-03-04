/**
 * @file severity.cpp
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


#include "config.hpp"
#include "severity_default.hpp"

namespace logcpp {

/**
 * @brief The names of severity_level as string array
 */
std::array < const std::string, 1 + (int)default_severity_levels::SEVERITY_SIZE >* DefaultSeverity::default_severity_names =
new std::array < const std::string, 1 + (int)default_severity_levels::SEVERITY_SIZE >
{{
	"off",
#if LOGCPP_ENABLE_COLOR_SUPPORT
#ifdef LOGCPP_AUTOCOLOR
	"\x1b[1;49;31mcritical\x1b[0m",
	"\x1b[0m\x1b[49;31m error  \x1b[0m",
	"\x1b[0m\x1b[1;49;33m warning\x1b[0m",
	"\x1b[0m\x1b[49;36m normal \x1b[0m",
	"\x1b[0m\x1b[1;49;36mverbose\x1b[0m",
	"\x1b[0m\x1b[1;49;36mverbose2\x1b[0m",
	"\x1b[0m\x1b[1;49;35m debug \x1b[0m",
	"\x1b[0m\x1b[1;49;35m debug2 \x1b[0m",
#else
	"critical",
	"error",
	"warning",
	"normal",
	"verbose",
	"verbose2",
	"debug",
	"debug2",
#endif
#else
	"critical",
	"error",
	"warning",
	"normal",
	"verbose",
	"verbose2",
	"debug",
	"debug2",
#endif
	"SIZE_T"
}};


DefaultSeverity::DefaultSeverity()
	:	AbstractSeverity< default_severity_levels >( DefaultSeverity::default_severity_names )
{}


const uint DefaultSeverity::max_name_length() {
	return 8;
}



} // namespace logcpp

