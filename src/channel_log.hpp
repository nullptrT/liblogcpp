/**
 * @file channel_log.hpp
 * @brief A logger with different channels
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: A intuitive and highly customizable LGPL library for logging with C++.
	Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
	Copyright (C) 2015-2016 Sebastian Lau <lauseb644@gmail.com>

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

#pragma once

#include "basic_log.hpp"

#include <map>

namespace logcpp {

/**
 * @brief A logger with different channels of type logger_t
 */
template< class logger_t >
class channellog {

	basic_log* m_default_channel;
	std::map< const std::string, logger_t* > m_channels;

public:
	/**
	 * @brief Constructor.
	 */
	channellog()
		:	m_default_channel( new basic_log() )
		,	m_channels()
	{}

	/**
	 * @brief Destructor
	 */
	~channellog() {}

	/**
	 * @brief Add a new logging channel with a given name
	 * @param channel_name Name of the new channel
	 * @param logger The logger that is to be added with that name
	 * @returns Wether the logger was added or not
	 */
	bool add_channel( const std::string channel_name, logger_t& logger ) {
		return m_channels.insert( std::make_pair(channel_name, &logger) ).second;
	}

	/**
	 * @brief This operator is used to access the channels by their name.
	 * @param channel_name The name of the channel to log to
	 * @returns A reference to the logger found or a default basic_log
	 * @note If no channel is found with this name, everything is logged to a basic_log on std::cout, no matter, if function are understood or not.
	 * @note Be careful not to have typos...
	 */
	logger_t& operator[] ( const std::string channel_name ) {
		try {
			logger_t* logger = m_channels.at( channel_name );
			return *logger;
		} catch ( std::out_of_range& oor ) {
			return *m_default_channel;
		}
	}
};

} // namespace logcpp

