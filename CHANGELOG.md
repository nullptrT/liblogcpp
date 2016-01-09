# LibLogC++
##### Changelog


## Noteworthy changes in release 1.7.1 (2016-01-09) [stable]

#### Changes in behavior

*	The compile options AUTOCOLOR and ENABLE_QT_SUPPORT are now prefixed with LOGCPP_ (LOGCPP_AUTOCOLOR, LOGCPP_ENABLE_QT_SUPPORT) for better compatibility with other libraries


## Noteworthy changes in release 1.7.0 (2016-01-08) [stable]

#### New features

*	Colorizing and controlling the font is supported for unix now

#### Changes in behavior

*	The compile and cmake option -DAUTOCOLOR=1 enables automatic features like colorizing severities and resetting terminal mode after ending a record.


## Noteworthy changes in release 1.6.3 (2016-01-01) [stable]

#### New features

*	Added support for QString. This can be enabled with the
	CMake option -DENABLE_QT_SUPPORT=ON



## Noteworthy changes in release 1.6.2 (2015-12-06) [stable]

#### New features

*	Added Doxygen documentation


## Noteworthy changes in release 1.6.1 (2015-11-20) [patch]

#### New features

*	Added packaging files for Debian 8 and later
	
*	Add pkg-config module

#### Bug Fixes

*	Fix installation of library headers (they were installed
	to include, not include/liblogcpp)




## Noteworthy changes in release 1.6.0 (2015-11-19) [stable]

#### New features

*	Added CMake modules
	
*	Added packaging files for Arch Linux
	
*	Added version header logcppversion.hpp

#### Bug Fixes

*	Some fixes in build system

#### Changes in behavior

*	The library (containing the global logger) can only be build static since this release.


## Noteworthy changes in release next (????-??-??) [?]

#### New features

*	

#### Bug Fixes

*	

#### Changes in behavior

*	




