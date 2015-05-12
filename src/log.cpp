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


/** File Version: 0.0.2-2 **/


#include "log.hpp"


namespace log {

std::string globallog::logfile = std::string( "./globallog.log" );
std::unique_ptr< globallog > globallog::log_;


globallog::globallog()
	:	severity_log< severity_level, severity_name >( normal ),
		console_log( new severity_logger() ),
		file_log_enabled_(false),
		ofs( new std::ofstream ),
		file_log( nullptr ),
		file_severity( normal )
{}

globallog& globallog::get() {

	if( !log_ ) {
		log_.reset( new globallog() );
	}

	return *log_;
}

void globallog::end_record() {
	*console_log << stream.get_buf() << endrec;

	if( file_log_enabled_ ) {
		*file_log << stream.get_buf() << endrec;
	}

	stream.clear_buf();
}


void globallog::set_max_console_severity(severity_level level) {
	this->max_severity_lvl = level;
	console_log->set_max_severity_level( level );
}


void globallog::set_max_file_severity(severity_level level) {
	file_log->set_max_severity_level( level );
	this->file_severity = level;
}


void globallog::set_max_severity_level(severity_level level) {
	set_max_console_severity( level );
	set_max_file_severity( level );
}

void globallog::set_logfile_impl() {
	if( ofs->is_open() ) { // Close the current file, if open
		ofs->close();
	}
	ofs->open( globallog::logfile, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
	file_log.reset( new severity_logger( ofs->rdbuf(), this->file_severity ) );
	file_log->enable_timestamp();
}

void globallog::set_logfile(const std::string file) {
	logfile = file;
	get().set_logfile_impl();
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




} // namespace log

