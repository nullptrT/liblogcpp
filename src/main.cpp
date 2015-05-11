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


/** File Version: 0.1.4-2 **/


#include "severity_logger.hpp"
#include "logmanip.hpp"
#include "log.hpp"

int main(int argc, char** argv) {

	log::severity_logger logger(log::verbose);

	logger << "A Simple message" << log::endrec;

	logger << std::setw(20) << "std::setw(20)" << log::endrec;

	logger << "42 as hex:" << std::hex << 42 << log::endrec;

	logger << "Message followed by std::endl" << log::endl << "Message after std::endl, followed by log::endrec" << log::endrec;

	logger << "First message" << "Message following";

	logger << log::endrec;

	logger << log::severity_level::debug << "And a debug message";

	logger << log::severity_level::critical << "A critical message" << log::endrec;

	logger << "And another critical message" << log::endrec;

	logger << log::normal << SCOPE << "A normal message with SCOPE following the severity." << log::endrec;

	logger << SCOPE << "A message with a SCOPE before" << log::endrec;

	logger << SCOPE_SEVERITY(log::error) << "A message calling SCOPE_SEVERITY(log::error)" << log::endrec;


	std::ofstream* ofs = new std::ofstream( "./flog_test.log", std::ofstream::out | std::ofstream::app | std::ofstream::ate);

	log::logger flog( ofs->rdbuf() );

	flog << SCOPE << "This log goes to a file" << log::endrec;

	log::severity_logger sflog( ofs->rdbuf() );

	sflog << log::error << SCOPE << "This is a second severity_logger to the same file" << log::endrec;

	log::globallog::enable_file_log();

	log::globallog::get() << SCOPE << "This is the first message using the global logger" << log::endrec;

	log::globallog::disable_file_log();

	log::globallog::get() << "This second global message was send after disabling the file log." << log::endrec;

	if( !stdlog.file_log_enabled() ) {
		log::globallog::enable_file_log();
	}

	log::globallog::get() << "Re-enabled file log" << log::endrec;

	log::globallog::get().set_max_console_severity( log::critical );

	log::globallog::get() << log::error << "This message goes to the file only, because console only accepts critical messages." << log::endrec;

	log::globallog::get() << log::critical << "Did you notice the previous global error message?" << log::endrec;

	stdlog << "This is sent with stdlog as alias for log::globallog::get()" << log::endrec;

	stdlog << "And again, 42 as hex via stdlog: " << std::hex << 42 << log::endrec;

	stdlog << "That's it for now." << log::endrec;


	return 0;
}

