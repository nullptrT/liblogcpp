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


/** File Version: 0.0.3-2 **/

#pragma once

#include <memory>
#include <fstream>

#include "severity_logger.hpp"

namespace logcpp {

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
	severity_level file_severity;

	globallog();
	globallog(globallog const& another) = delete;
	globallog& operator=(globallog const& another);

	void enable_console_log_impl();
	void disable_console_log_impl();
	void enable_file_log_impl();
	void disable_file_log_impl();
	void set_logfile_impl();

public:


	static globallog& get();

	inline logcpp::globallog& operator<<(globallog& (*f)(globallog&)) {
		return f(*this);
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
	 * Sets the maximum severity for both logs (console and file)
	 */
	void set_max_severity_level( severity_level level);

	/*
	 * Sets wether to use timestamps on console or not
	 */
	void use_timestamps_console( bool use = true );

	/*
	 * Sets wether to use timestamps on console or not
	 */
	void use_timestamps_file( bool use = true );

	/*
	 * Overrides of the two functions from basic_log
	 * Enables or disables timestamps for both loggers - console and file
	 */
	void enable_timestamp();
	void disable_timestamp();

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

	bool console_log_enabled() const;
	bool file_log_enabled() const;

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
		if( this->stream.has_buffered_content() ) {
			this->log< std::string >( this->stream.get_buf() );
		}

		*console_log << severity;

		if( file_log_enabled_ ) {
			*file_log << severity;
		}

		this->current_severity = severity;
	}
};

} // namespace logcpp

#define stdlog logcpp::globallog::get()
