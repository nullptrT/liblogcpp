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


/** File Version: 0.0.1-2 **/

namespace logcpp {

template< typename severity_t >
class severity_feature
{
protected:
	severity_t max_severity_lvl;
	severity_t current_severity;

	explicit severity_feature( severity_t max_severity )
		:	max_severity_lvl( max_severity )
	{}
	severity_feature( const severity_feature& ) = delete;

	bool log_enabled() const {
		return ( current_severity <= max_severity_lvl && max_severity_lvl != 0 ); // A severity of 0 should default to 'logging off'
	}

public:
	/*
	 * Specify, how much output the Logger will produce
	 */
	void set_max_severity_level(const severity_t severity ) {
		max_severity_lvl = severity;
	}

	const severity_t severity_max() const { return max_severity_lvl; }
	const severity_t severity() const { return current_severity; }

};


} // namespace logcpp

