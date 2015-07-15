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


/** File Version: 0.0.1-4 **/

#pragma once

#include <string>
#include <array>


namespace logcpp {

enum severity_level {
	off,
	critical,
	error,
	warning,
	normal,
	verbose,
	debug
};

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


inline const std::string severity_name(severity_level lvl) {
	if( static_cast< std::size_t >(lvl) < names.size() ) {
		return names[lvl];
	} else {
		return names.back();
	}
}

} // namespace logcpp

