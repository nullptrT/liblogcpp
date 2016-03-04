/**
 * @file log.cpp
 * @brief A global singleton logger with severities that has a console and a file channel
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


#include "log.hpp"
#include "logcppversion.hpp"


namespace logcpp {

std::string globallog::logfile = std::string( "./globallog.log" );
std::unique_ptr< globallog > globallog::log_;


globallog::globallog()
	:	severity_log< default_severity_levels >( new DefaultSeverity(), normal ),
		console_log( new severity_logger() ),
		file_log_enabled_(false),
		ofs( new std::ofstream ),
		file_log( nullptr ),
		file_severity( normal )
{}

globallog& globallog::get() {

	if( !log_ ) {
		log_.reset( new globallog() );
		stdlog.enable_print_severity(false);
		stdlog << logcpp::warning;
#ifdef LOGCPP_AUTOCOLOR
		stdlog << logcpp::sty_bold;
#endif
		stdlog << "LibLogC++ v" << LIBLOGCPP_DOTTED_VERSION << " (https://git.io/vBW7r)";
#ifdef LOGCPP_AUTOCOLOR
		stdlog << logcpp::ctl_reset_all;
#endif
		stdlog << logcpp::endrec;
		stdlog.enable_print_severity();
	}

	return *log_;
}

void globallog::end_record() {
	*console_log << stream.get_buf() << endrec;

	if( file_log_enabled_ ) {
		*file_log << stream.get_buf() << endrec;
	}

	stream.clear_buf();

	if( this->current_severity == critical && abort_f != nullptr ) {
		abort_f();
	}
}

void globallog::end_line () {
	*console_log << endl;

	if( file_log_enabled_ ) {
		*file_log << endl;
	}
}


void globallog::set_max_console_severity(default_severity_levels level) {
	this->max_severity_lvl = level;
	console_log->set_max_severity_level( level );
}


void globallog::set_max_file_severity(default_severity_levels level) {
	if ( file_log_enabled_ ) {
		file_log->set_max_severity_level( level );
	}
	this->file_severity = level;
}


void globallog::set_max_severity_level(default_severity_levels level) {
	set_max_console_severity( level );
	set_max_file_severity( level );
}

void globallog::set_logfile_impl() {
	if( ofs->is_open() ) { // Close the current file, if open
		ofs->close();
	}
	ofs->open( globallog::logfile, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
	file_log.reset( new severity_logger( ofs->rdbuf(), this->file_severity ) );
	file_log->enable_print_severity(false);
	*file_log << logcpp::warning << "LibLogC++ v" << LIBLOGCPP_DOTTED_VERSION << " (https://git.io/vBW7r)" << logcpp::endrec;
	file_log->enable_print_severity();
	file_log->enable_timestamp();
}

void globallog::set_logfile(const std::string file) {
	logfile = file;
	get().set_logfile_impl();
}

void globallog::use_timestamps_console(bool use) {
	if(use) console_log-> enable_timestamp();
	else console_log->disable_timestamp();
}

void globallog::use_timestamps_file(bool use) {
	if( !file_log ) {
		set_logfile_impl();
	}
	if(use) file_log-> enable_timestamp();
	else file_log->disable_timestamp();
}

void globallog::enable_timestamp() {
	use_timestamps_console();
	use_timestamps_file();
	basic_log::enable_timestamp();
}

void globallog::disable_timestamp() {
	use_timestamps_console(false);
	use_timestamps_file(false);
	basic_log::disable_timestamp();
}

void globallog::enable_print_severity( bool enable ) {
	console_log->enable_print_severity( enable );

	if( file_log_enabled_ ) {
		file_log->enable_print_severity( enable );
	}
}

void globallog::enable_console_log_impl() {
	console_log->set_max_severity_level( this->max_severity_lvl );
}

void globallog::enable_console_log() {
	get().enable_console_log_impl();
}

void globallog::disable_console_log_impl() {
	console_log->set_max_severity_level( off );
}

void globallog::disable_console_log() {
	get().disable_console_log_impl();
}

void globallog::enable_file_log_impl() {
	if( !file_log ) {
		set_logfile_impl();
	}
	file_log->set_max_severity_level( this->file_severity );
	file_log_enabled_ = true;
}

void globallog::enable_file_log() {
	get().enable_file_log_impl();
}

void globallog::disable_file_log_impl() {
	file_log->set_max_severity_level( off );
	file_log_enabled_ = false;
}

void globallog::disable_file_log() {
	get().disable_file_log_impl();
}

bool globallog::console_log_enabled() const {
	return ( console_log
			 && console_log->severity_max() != off );
}

bool globallog::file_log_enabled() const {
	return (file_log_enabled_
			&& file_log
			&& file_log->severity_max() != off );
}




} // namespace logcpp

