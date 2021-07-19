/**
 * @file color_feature.cpp
 * @brief Functions and enums needed for controlling the style and colors of a terminal
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: An intuitive and highly customizable LGPL library for logging with C++.
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


#include "color_feature.hpp"

#ifdef LOGCPP_ENABLE_COLOR_SUPPORT

namespace logcpp {

color_feature::color_feature()
	:	m_background_ctl( false )
	,	m_back( 49 )
	,	m_fore( 39 )
	,	m_styles()
{}


const std::string color_feature::code(termmode m) {
	bool set = true;
	bool disable_blink = false;
	switch( m ) {
		case ctl_reset_col:
			m_back = 49;
			m_fore = 39;
			break;
		case ctl_reset_all:
			m_back = 49;
			m_fore = 39;
			m_styles.clear();
			m_background_ctl = false;
			return std::string("\x1b[0m");
		case col_white:
			if ( !m_background_ctl ) {
				m_fore = 37;
			} else {
				m_back = 47;
			}
			break;
		case col_cyan:
			if ( !m_background_ctl  ) {
				m_fore = 36;
			} else {
				m_back = 46;
			}
			break;
		case col_magenta:
			if ( !m_background_ctl  ) {
				m_fore = 35;
			} else {
				m_back = 45;
			}
			break;
		case col_blue:
			if ( !m_background_ctl  ) {
				m_fore = 34;
			} else {
				m_back = 44;
			}
			break;
		case col_yellow:
			if ( !m_background_ctl  ) {
				m_fore = 33;
			} else {
				m_back = 43;
			}
			break;
		case col_green:
			if ( !m_background_ctl  ) {
				m_fore = 32;
			} else {
				m_back = 42;
			}
			break;
		case col_red:
			if ( !m_background_ctl  ) {
				m_fore = 31;
			} else {
				m_back = 41;
			}
			break;
		case col_black:
			if ( !m_background_ctl ) {
				m_fore = 30;
			} else {
				m_back = 40;
			}
			break;
		case sty_bold:
			for ( unsigned int i : m_styles ) {
				if ( i == 1 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(1);
			}
			break;
		case sty_unterline:
			for ( unsigned int i : m_styles ) {
				if ( i == 4 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(4);
			}
			break;
		case sty_blink:
			for ( unsigned int i : m_styles ) {
				if ( i == 5 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(5);
			}
			break;
		case sty_blink_off:
			for ( std::vector< unsigned int >::iterator it = m_styles.begin(); it != m_styles.end(); it++ ) {
				if ( *it == 5 ) {
					m_styles.erase(it);
					disable_blink = true;
				}
			}
			break;
		case ctl_background:
			m_background_ctl = true;
			return std::string("");
		case ctl_foreground:
			m_background_ctl = false;
			return std::string("");
		default:
			return std::string("");
	}

	std::string ansi_code("\x1b[");
	for( unsigned int i : m_styles ) {
		ansi_code += std::to_string(i) + ";";
	}
	if ( disable_blink ) {
		ansi_code += std::to_string(25) + ";";
	}
	ansi_code += std::to_string(m_fore) + ";";
	ansi_code += std::to_string(m_back) + "m";
	
	return ansi_code;
}


const std::string color_feature::code_plain(termmode m) {
	switch( m ) {
		case ctl_reset_col:
			return std::string("\x1b[39m");
		case ctl_reset_all:
			return std::string("\x1b[0m");
		case col_white:
			return std::string("\x1b[37m");
		case col_cyan:
			return std::string("\x1b[36m");
		case col_magenta:
			return std::string("\x1b[35m");
		case col_blue:
			return std::string("\x1b[34m");
		case col_yellow:
			return std::string("\x1b[33m");
		case col_green:
			return std::string("\x1b[32m");
		case col_red:
			return std::string("\x1b[31m");
		case col_black:
			return std::string("\x1b[30m");
		case sty_bold:
			return std::string("\x1b[1m");
		case sty_unterline:
			return std::string("\x1b[4m");
		case sty_blink:
			return std::string("\x1b[5m");
		case sty_blink_off:
			return std::string("\x1b[25m");
		default:
			return std::string("");
	}
}


} // namespace logcpp

#endif

