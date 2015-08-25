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



/** File Version: 0.0.5-3 **/


#pragma once

#include "logstream.hpp"


#include <utility>
#include <iostream>
#include <sstream>

extern "C" {
#include <ctime>
}




namespace logcpp {

typedef std::pair< std::string, uint > scope_t;
inline scope_t scope(std::string place, uint line) {
	return scope_t( place, line);
}

#define SCOPE logcpp::scope(__FILE__, __LINE__)

inline const std::string timestr() {
	std::time_t rawtime = std::time(0);
	struct std::tm* tinfo;
	tinfo = std::localtime(&rawtime);
	char buf[22];
	std::strftime(buf, 22, "%F_%T", tinfo);
	return std::string(buf);
}

#define TIME logcpp::timestr()


class basic_log
{
public:

	inline basic_log& operator<<(basic_log& (*f)(basic_log& l)) {
		return f(*this);
	}

	template< typename T >
	inline basic_log& operator<<(const T& t) {
		log<T>(t);
		return *this;
	}

	template< typename ret, typename param >
	friend basic_log& operator<<(basic_log& logger, ret (*f)(param)) {
		logger.stream << f;
		return logger;
	}

protected:
	logstreambuf stream;
	bool timestamp_enabled_;

	void insert_time_or_not() {
		if(timestamp_enabled_) {
			stream << "[" << timestr() << "] - ";
		}
	}

	bool new_record;

public:

	/*
	 * Specify, where to log to
	 */
	explicit basic_log( std::streambuf* outbuf = std::cout.rdbuf() )
		:	stream( outbuf ),
			timestamp_enabled_(false),
			new_record(true)
	{}
	basic_log( const basic_log& ) = delete;
	~basic_log() {}

	void end_record() {
		stream << "\n";
		stream.flush();
		new_record = true;
	}

	void enable_timestamp() { timestamp_enabled_ = true; }
	void disable_timestamp() { timestamp_enabled_ = false; }

	void end_line() {
		stream << "\n";
		new_record = false;
	}

	template< typename T >
	void log( const scope_t& scope) {
		if( new_record ) insert_time_or_not();
		stream << "[ " << scope.first << ":" << scope.second << " ] : ";
		new_record = false;
	}

	template< typename T >
	void log(const T& t) {
		if( new_record ) insert_time_or_not();
		stream << t;
		new_record = false;
	}

};


template< typename logger_t >
inline logger_t& endrec(logger_t& out) {
	out.end_record();
	return out;
}

template< typename logger_t >
inline logger_t& endl(logger_t& out) {
	out.end_line();
	return out;
}

template basic_log& endl(basic_log&);

typedef basic_log logger;

} // namespace logcpp


