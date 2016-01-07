/**
 * @file color_feature.cpp
 * @brief Functions and enums needed for controlling the style and colors of a terminal
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

/** File Version: 0.0.1-1 **/

#include "color_feature.hpp"

#ifdef ENABLE_COLOR_SUPPORT

namespace logcpp {

color_feature* color_feature::m_self = 0;

color_feature::color_feature()
	:	m_background_ctl( false )
	,	m_back( 49 )
	,	m_fore( 39 )
	,	m_styles()
{}


color_feature& color_feature::get() {
	if ( m_self == 0 ) {
		m_self = new color_feature();
	}
	return *m_self;
}


const std::string color_feature::code(color c) {
	bool set = true;
	bool disable_blink = false;
	switch( c ) {
		case ctl_reset_col:
			m_back = 49;
			m_fore = 39;
			break;
		case ctl_reset_all:
			m_back = 49;
			m_fore = 39;
			m_styles.clear();
			return std::string("\x1b[0m");
		case white:
			if ( !m_background_ctl ) {
				m_fore = 37;
			} else {
				m_back = 47;
			}
			break;
		case cyan:
			if ( !m_background_ctl  ) {
				m_fore = 36;
			} else {
				m_back = 46;
			}
			break;
		case magenta:
			if ( !m_background_ctl  ) {
				m_fore = 35;
			} else {
				m_back = 45;
			}
			break;
		case blue:
			if ( !m_background_ctl  ) {
				m_fore = 34;
			} else {
				m_back = 44;
			}
			break;
		case yellow:
			if ( !m_background_ctl  ) {
				m_fore = 33;
			} else {
				m_back = 43;
			}
			break;
		case green:
			if ( !m_background_ctl  ) {
				m_fore = 32;
			} else {
				m_back = 42;
			}
			break;
		case red:
			if ( !m_background_ctl  ) {
				m_fore = 31;
			} else {
				m_back = 41;
			}
			break;
		case black:
			if ( !m_background_ctl ) {
				m_fore = 30;
			} else {
				m_back = 40;
			}
			break;
		case sty_bold:
			for ( uint i : m_styles ) {
				if ( i == 1 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(1);
			}
			break;
		case sty_unterline:
			for ( uint i : m_styles ) {
				if ( i == 4 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(4);
			}
			break;
		case sty_blink:
			for ( uint i : m_styles ) {
				if ( i == 5 ) {
					set = false;
				}
			}
			if (set) {
				m_styles.push_back(5);
			}
			break;
		case sty_blink_off:
			for ( std::vector< uint >::iterator it = m_styles.begin(); it != m_styles.end(); it++ ) {
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
	for( uint i : m_styles ) {
		ansi_code += std::to_string(i) + ";";
	}
	if ( disable_blink ) {
		ansi_code += std::to_string(25) + ";";
	}
	ansi_code += std::to_string(m_fore) + ";";
	ansi_code += std::to_string(m_back) + "m";
	
	return ansi_code;
}

} // namespace logcpp

#endif

