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



/** File Version: 0.0.4-1 **/

#pragma once

#include "basic_log.hpp"
#include "severity_feature.hpp"


namespace log {


template< typename severity_t, const std::string (*severity_name)(severity_t) >
class severity_log
	:	public basic_log,
		public severity_feature< severity_t >
{
protected:
	void(*abort_f)(void);
public:
	inline severity_log& operator<<(severity_log& (*f)(severity_log&)) {
		return f(*this);
	}

	template< typename T >
	inline severity_log& operator<<(const T& t) {
		log<T>(t);
		return *this;
	}

	explicit severity_log( severity_t severity, std::streambuf* outbuf = std::cout.rdbuf())
		:	basic_log(outbuf),
			severity_feature< severity_t >(severity),
			abort_f(nullptr)
	{}
	severity_log( const severity_log& ) = delete;

	void end_record() {
		if( this->log_enabled() ) {
			basic_log::end_record();
			if( this->current_severity == 1 && abort_f != nullptr ) {
				abort_f();
			}
		} else {
			stream.clear_buf();
			new_record = true;
		}
	}

	/*
	 * Sets the function to be used when a critical record has been written (defaults to no function)
	 */
	void set_critical_log_function( void(*crit_f)(void) = nullptr ) {
		abort_f = crit_f;
	}

	template< typename T >
	void log( const T& t) {
		if( new_record ) {
			insert_time_or_not();
			stream << "<" << severity_name( this->current_severity ) << ">: ";
			new_record = false;
		}
		basic_log::log<T>(t);
	}

	template< typename T >
	void log( const severity_t& severity) {
		if( !new_record && stream.has_buffered_content() ) {
			this->end_record();	// Flush buffer with previous severity before changing the current
		} else if( new_record ) {
			insert_time_or_not();
		}
		this->current_severity = severity;
		stream << "<" << severity_name( this->current_severity ) << ">: ";
		new_record = false;
	}

	typedef std::pair< severity_t, scope_t > severity_scope_t;
	static severity_scope_t severity_scope( severity_t severity, scope_t scope ) {
		return severity_scope_t( severity, scope );
	}

	template< typename T >
	void log( const severity_scope_t& sev_scope ) {
		this->log< severity_t >(sev_scope.first);
		this->log< scope_t >(sev_scope.second);
	}

};



} // namespace log



