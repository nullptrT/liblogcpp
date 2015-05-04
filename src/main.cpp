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


#include "log.hpp"

#include <iostream>

int main(int argc, char** argv) {

	log::stdlog::disable_file_log();
	//log::std_log* logger = new log::std_log();

	*log::stdlog::get() << "A Simple message" << log::endrec;

	/**logger << "Message followed by std::endl" << log::endl << "Message after std::endl, followed by log::endrec" << log::endrec;

	*logger << "A normal message followed by two log::endrec" << log::endrec << log::endrec;

	*logger << "First message" << "Message following";

	*logger << log::endrec;

	*logger << log::severity_level::debug << "And a debug message";

	*logger << log::severity_level::critical << "A critical message" << log::endrec;*/



	return 0;
}

