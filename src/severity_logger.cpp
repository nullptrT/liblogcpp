/**
 * @file severity_logger.cpp
 * @brief A severity logger that can be used instantly
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
    LibLogC++: A intuitive and highly customizable LGPL library for logging with C++.
    Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
    Copyright (C) 2015-2021 Sebastian Lau <lauseb644@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

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


namespace logcpp {

/**
 * @brief Creates severity_logger logging to std::cout
 * @param max_severity The maximum severity level for this logger
 */
severity_logger::severity_logger( default_severity_levels max_severity )
    :	severity_log< default_severity_levels >( new DefaultSeverity(), max_severity )
{
    this->current_severity = normal;
}

/**
 * @brief Creates severity_logger logging to a specific streambuf
 * @param stream A pointer to some std::streambuf where all content is logged to.
 * @param max_severity The maximum severity level for this logger
 */
severity_logger::severity_logger( std::streambuf* stream, default_severity_levels max_severity )
    :	severity_log< default_severity_levels >( new DefaultSeverity(), max_severity, stream)
{
    this->current_severity = normal;
}


severity_logger::~severity_logger() {}


/**
 * @brief Function that optionally inserts colors for severities
 * @param severity Severity level severity level to log
 */
void severity_logger::log_severity( const default_severity_levels severity ) {
    this->current_severity = severity;
#ifdef LOGCPP_AUTOCOLOR
    if ( severity != off && severity != SEVERITY_SIZE && severity != normal ) {
        if ( severity == critical ) {
            severity_log::log<termmode>(col_red);
            severity_log::log<termmode>(sty_bold);
        } else if ( severity == error ) {
            severity_log::log<termmode>(col_red);
        } else if ( severity == warning ) {
            severity_log::log<termmode>(col_yellow);
        } else if ( severity == verbose ) {
            severity_log::log<termmode>(col_cyan);
        } else if ( severity == verbose2 ) {
            severity_log::log<termmode>(col_blue);
        } else if ( severity == debug ) {
            severity_log::log<termmode>(col_cyan);
            severity_log::log<termmode>(sty_bold);
        } else if ( severity == debug2 ) {
            severity_log::log<termmode>(col_white);
            severity_log::log<termmode>(sty_bold);
        }
    }
#endif
    severity_log::log_severity( severity );
#ifdef LOGCPP_AUTOCOLOR
    if ( severity != off && severity != SEVERITY_SIZE && severity != normal ) {
        severity_log::log<termmode>(ctl_reset_all);
    }
#endif
}


} // namespace logcpp
