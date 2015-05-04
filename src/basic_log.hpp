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


/** File Version: 0.0.1-1 **/

#pragma once

#include "logstream.hpp"


#include <utility>
#include <iostream>




namespace log {

typedef std::pair< std::string, uint > scope_t;
inline scope_t scope(std::string place, uint line) {
	return scope_t( place, line);
}

#define SCOPE log::scope(__FILE__, __LINE__)



class basic_log
{
public:

	inline basic_log& operator<<(basic_log& (*f)(basic_log& l)) {
		return f(*this);
	}

protected:
	logstreambuf stream;

public:

	/*
	 * Specify, where to log to
	 */
	explicit basic_log( std::streambuf* outbuf = std::cout.rdbuf() )
		:	stream( outbuf )
	{}
	basic_log( const basic_log& ) = delete;
	~basic_log() {}

	void end_record() {
		stream.flush();
	}

	void end_line() {
		stream << "\n";
	}

	template< typename T >
	void log( const scope_t& scope) {
		stream << "[ " << scope.first << ":" << scope.second << " ] : ";
	}

	template< typename T >
	void log(const T& t) {
		stream << t;
	}

};


template< typename logger_t >
inline logger_t& endrec(logger_t& out) {
	out.end_record();
	return out;
}

//template basic_log& endrec(basic_log&);

template< typename logger_t >
inline logger_t& endl(logger_t& out) {
	out.end_line();
	return out;
}

template basic_log& endl(basic_log&);

} // namespace log



template< typename T >
inline log::basic_log& operator<<(log::basic_log& out, const T& t) {
	out.log<T>(t);
	return out;
}

