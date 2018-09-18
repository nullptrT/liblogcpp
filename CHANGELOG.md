# LibLogC++
##### A intuitive and highly customizable LGPL library for logging with C++.
##### Changelog


## Important changes in release 1.9.4 (2018-09-18) [stable]

### Changes in behavior

* Disable color feature (ANSI codes in strings are not supported anymore)

#### Patches

* Patch main.cpp for testing and examples
* Make it possible to disable the version prompt when starting globallog
* Small patch to uint syntax for windows


## Noteworthy changes in release 1.9.3 (2017-09-27) [stable]

#### Patches

* Add missing inline to QString compatibility function


## Noteworthy changes in release 1.9.2 (2017-04-01) [stable]

#### Changes in behavior

* More member functions are protected now

#### Bug fixes

* Patched destructors that should be virtual causing compilation errors on windows (msvc2015)


## Noteworthy changes in release 1.9.1 (2017-01-14) [stable]

#### Changes in behavior

* The way, `QString` is handled changed: The core library is not linked against `Qt5Core` anymore. Instead there is a conversion header `logcpp-qt.hpp` included in the release that enables the log buffer to handle `QString`. This header has to be included in some of your files that want to pass `QString`s to loggers. The CMake-Option `LOGCPP_ENABLE_QT_SUPPORT` does not exist anymore.
* `severity_logger` now colors severities by default, if on unix. The CMake-Option `LOGCPP_AUTOCOLOR` does not exist anymore.

#### Bug fixes

* `QString` can be handled properly when liblogcpp is not used as a git submodule and its compilation does not react to the own flags


## Noteworthy changes in release 1.9.0 (2016-10-07) [stable]

#### New features

* Assertion functions aviable via the header `assert.hpp`
* channel_log now supports logging to all channels enabled at once

#### Changes in behaviour

* For class name conveniences channellog is now called channel_log. There is a typedef channellog, so you haven't to change anything


## Noteworthy changes in release 1.8.1 (2016-05-14) [stable]

#### Changes in behaviour

* The directory prefix of a scope is now stripped by default. The compiler option therefore changed to `LOGCPP_LEAVE_SCOPE_DIRS_PREFIX` to prevent this behaviour

#### Bug fixes

* Color codes are not logged to file logs any more
* LOGCPP_AUTOCOLOR is now implemented as member functions and only logs, if m_color_ok is true
* Resetting the Color mode also resets the ctl_foreground/ctl_background flag now


## Noteworthy changes in release 1.8.0 (2016-03-05) [stable]

#### New features

* liblogcpp has now a channel logger that is able to handle a set of named loggers that can be selected by operator[]


## Noteworthy changes in release 1.7.3 (2016-03-05) [stable]

#### New features

* liblogcpp now supports MSVC 2015 and later (Tested on Windows 8.1). There is still no solution for colors on Windows.


## Noteworthy changes in release 1.7.2 (2016-03-04) [stable]

#### New features

* liblogcpp can now be build as shared library by passing `-DLOGCPP_SHARED=ON` to cmake. Default behaviour is to build a static library.
* Severities are not defined in global namespace anymore, but in classes that can be inherited from.

#### Changes in behavior

* The cmake options AUTOCOLOR, ENABLE_QT_SUPPORT and INSTALL_LIBS are now also prefixed with LOGCPP_ (LOGCPP_AUTOCOLOR, LOGCPP_ENABLE_QT_SUPPORT, LOGCPP_INSTALL_LIBS) for better compatibility with other libraries when used as a submodule.
* The make target for Doxygen is now called 'doc_logcpp' for compatibility when using this as a submodule.
* The make target is now enabled automatically when Doxygen is found.
* Less templating, less compile time

#### Bug fixes

* Don't make it possible to use AUTOCOLOR on WIN32 yet
* Color support is now explicitly disabled for WIN32 in config.hpp, even if CMake sets this macro
* The file liblogcpp.pc is now configured according to the environment


## Noteworthy changes in release 1.7.1 (2016-01-09) [stable]

#### Changes in behavior

* The compile options AUTOCOLOR and ENABLE_QT_SUPPORT are now prefixed with LOGCPP_ (LOGCPP_AUTOCOLOR, LOGCPP_ENABLE_QT_SUPPORT) for better compatibility with other libraries


## Noteworthy changes in release 1.7.0 (2016-01-08) [stable]

#### New features

* Colorizing and controlling the font is supported for unix now

#### Changes in behavior

* The compile and cmake option -DAUTOCOLOR=1 enables automatic features like colorizing severities and resetting terminal mode after ending a record.


## Noteworthy changes in release 1.6.3 (2016-01-01) [stable]

#### New features

* Added support for QString. This can be enabled with the
  CMake option -DENABLE_QT_SUPPORT=ON



## Noteworthy changes in release 1.6.2 (2015-12-06) [stable]

#### New features

* Added Doxygen documentation


## Noteworthy changes in release 1.6.1 (2015-11-20) [patch]

#### New features

* Added packaging files for Debian 8 and later
* Add pkg-config module

#### Bug Fixes

* Fix installation of library headers (they were installed
  to include, not include/liblogcpp)




## Noteworthy changes in release 1.6.0 (2015-11-19) [stable]

#### New features

* Added CMake modules
* Added packaging files for Arch Linux
* Added version header logcppversion.hpp

#### Bug Fixes

* Some fixes in build system

#### Changes in behavior

* The library (containing the global logger) can only be build static since this release.


## Noteworthy changes in release next (????-??-??) [?]

#### New features

*	

#### Bug Fixes

*	

#### Changes in behavior

*	




