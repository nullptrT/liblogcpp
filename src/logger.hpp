/*
	liblogcpp: A simple, but highly customizable LGPL library for logging with C++.
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

#include "basic_log.hpp"


namespace log {

typedef basic_log logger;

class file_logger
	:	public basic_log
{
public:
	explicit file_logger( std::string file )
		:	basic_log( std::ofstream( file, std::ios_base::out | std::ios_base::app | std::ios_base::ate ).rdbuf() )
	{}
	file_logger( const file_logger& ) = delete;
};

} // namespace log

