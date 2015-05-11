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


/** File Version: 0.0.1-1 **/

#pragma once

//#include <boost/smart_ptr/scoped_ptr.hpp>

#include <memory>
#include "severity_logger.hpp"

namespace log {

class globallog
	:	public severity_log< severity_level, severity_name >
{
private:
	static std::unique_ptr< globallog > log_;

	static std::string logfile;
	std::unique_ptr< severity_logger > console_log;
	bool file_log_enabled_;
	std::ofstream* ofs;
	std::unique_ptr< severity_logger > file_log;

	globallog(std::ofstream* filestream );
	globallog(globallog const& another) = delete;
	globallog& operator=(globallog const& another);

	void enable_console_log_impl();
	void disable_console_log_impl();
	void enable_file_log_impl();
	void disable_file_log_impl();
	void set_logfile_impl();

public:


	static globallog& get();

	inline log::globallog& operator<<(globallog& (*f)(globallog&)) {
		return f(*this);
		//return out;
	}

	template< typename T >
	inline globallog& operator<<(const T& t) {
		this->log<T>(t);
		return *this;
	}


	/*
	 * Set a file to log to
	 */
	static void set_logfile( std::string file );

	/*
	 * Sets the maximum severity of message sent to console
	 */
	void set_max_console_severity( severity_level level );

	/*
	 * Sets the maximum severity of message sent to log file
	 */
	void set_max_file_severity( severity_level level );

	/*
	 * Enables logging to console
	 */
	static void enable_console_log();

	/*
	 * Disables logging to console
	 */
	static void disable_console_log();

	/*
	 * Enables logging to a file
	 */
	static void enable_file_log();

	/*
	 * Disables logging to a file
	 */
	static void disable_file_log();

	void end_record();

	template< typename T >
	void log( const T& t) {
		*console_log << t;

		if( file_log_enabled_ ) {
			*file_log << t;
		}
	}

	template< typename T >
	void log( const severity_level& severity ) {
		this->end_record();
		*console_log << severity;

		if( file_log_enabled_ ) {
			*file_log << severity;
		}

		this->current_severity = severity;
	}
};

} // namespace log

#define stdlog log::globallog::get()
