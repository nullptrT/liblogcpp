/**
 * @file color_feature.hpp
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

#pragma once

#include "config.hpp"

#ifdef ENABLE_COLOR_SUPPORT

#include <string>
#include <vector>


namespace logcpp {

enum color {
	// Default colors
	white,
	cyan,
	magenta,
	blue,
	yellow,
	green,
	red,
	black,

	// Styles
	sty_bold,
	sty_unterline,
	sty_blink,
	sty_blink_off,
	
	// Control
	ctl_reset_col,
	ctl_reset_all,
	ctl_foreground,
	ctl_background
};


class color_feature {
	
	static color_feature* m_self;
	color_feature();
	color_feature(color_feature const& another) = delete;
	color_feature& operator=(color_feature const& another);
	
	bool m_background_ctl;
	uint m_back;
	uint m_fore;
	std::vector< uint > m_styles;
public:
	/**
	 * @brief Get a reference to the color color feature
	 */
	static color_feature& get();
	
	const std::string code( color col );
};



} // namespace logcpp

#endif
