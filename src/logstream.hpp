/*
	liblogcpp: an simple, but highly customizable LGPL library for logging in C++.
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


/** File Version: 0.0.1-1 **/

#pragma once




#include <ostream>
#include <sstream>




namespace log {


class logstreambuf
	:	public std::ostream
{
	class logbuffer
		:	public std::stringbuf
	{
		std::ostream out;
	public:
		logbuffer(std::streambuf* outbuf)
			:	out( outbuf )
		{}

		virtual int sync() {
			out << str() << "\n";
			str("");
			out.flush();
			return 0;
		}
	};

	logbuffer buf;

public:
	logstreambuf( std::streambuf* outbuf )
		:	std::ostream(&buf),
			buf( outbuf )
	{}

	void clear_buf() {
		buf.str("");
		flush();
	}

	const std::string get_buf() const {
		return buf.str();
	}
};

} // namespace log


