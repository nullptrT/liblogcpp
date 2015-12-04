/*
	LibLogC++: A simple, but highly customizable and intuitive LGPL library for logging with C++.
	Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
	Copyright (C) 2015 Sebastian Lau <lauseb644@gmail.com>

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



#include "severity_logger.hpp"
#include "logmanip.hpp"
#include "log.hpp"
#include "log_exception.hpp"

int main(int argc, char** argv) {

	logcpp::severity_logger logger(logcpp::verbose);

	logger << "A Simple message" << logcpp::endrec;

	logger << std::setw(20) << "std::setw(20)" << logcpp::endrec;

	logger << "42 as hex:" << std::hex << 42 << logcpp::endrec;

	logger << "Message followed by std::endl" << logcpp::endl << "Message after std::endl, followed by logcpp::endrec" << logcpp::endrec;

	logger << "First message" << "Message following";

	logger << logcpp::endrec;

	logger << logcpp::severity_level::debug << "And a debug message";

	logger << logcpp::severity_level::critical << "A critical message" << logcpp::endrec;

	logger << "And another critical message" << logcpp::endrec;

	logger << logcpp::normal << SCOPE << "A normal message with SCOPE following the severity." << logcpp::endrec;

	logger << SCOPE << "A message with a SCOPE before" << logcpp::endrec;

	logger << SCOPE_SEVERITY(logcpp::error) << "A message calling SCOPE_SEVERITY(logcpp::error)" << logcpp::endrec;


	std::ofstream* ofs = new std::ofstream( "./flog_test.log", std::ofstream::out | std::ofstream::app | std::ofstream::ate);

	logcpp::logger flog( ofs->rdbuf() );

	flog << SCOPE << "This log goes to a file" << logcpp::endrec;

	logcpp::severity_logger sflog( ofs->rdbuf() );
	sflog.set_critical_log_function(logcpp::abort_with_exception);

	try {
		sflog << logcpp::critical << SCOPE << "This is a second severity_logger to the same file" << logcpp::endrec;
	} catch( logcpp::critical_exception& ce ) {
		logger << "When using sflog with logcpp::critical, there was a logcpp::critical_exception thrown:" << ce.what() << logcpp::endl << "It was catched, but the next critical message through the global logger will use std::abort()..." << logcpp::endrec;
	}

	logcpp::globallog::enable_file_log();

	logcpp::globallog::get() << SCOPE << "This is the first message using the global logger" << logcpp::endrec;

	logcpp::globallog::disable_file_log();

	logcpp::globallog::get() << "This second global message was send after disabling the file log." << logcpp::endrec;

	if( !stdlog.file_log_enabled() ) {
		logcpp::globallog::enable_file_log();
	}

	logcpp::globallog::get() << "Re-enabled file log" << logcpp::endrec;

	logcpp::globallog::get().set_max_console_severity( logcpp::error );

	logcpp::globallog::get() << logcpp::warning << "This message goes to the file only, because console only accepts critical messages." << logcpp::endrec;

	logcpp::globallog::get() << logcpp::critical << "Did you notice the previous global warning message?" << logcpp::endrec;

	stdlog << "This is sent with stdlog as alias for logcpp::globallog::get()" << logcpp::endrec;

	stdlog << "And again, 42 as hex via stdlog: " << std::hex << 42 << logcpp::endrec;

	stdlog << "And the current time: " << TIME << logcpp::endrec;

	stdlog.set_critical_log_function(std::abort);

	stdlog << logcpp::critical << "That's it for now." << logcpp::endrec;


	return 0;
}

