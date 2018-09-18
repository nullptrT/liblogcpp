# LibLogC++
##### An intuitive and highly customizable LGPL library for logging with C++
###### v1.9.3

This library aims to be simple, but highly usable and customizable without having a bunch of other unused dependencies, libraries or code.
It is a simple and intuitive frontend to libstdc++ turning it into a fully featured and easy to use general purpose logger.

* [Online api documentation](https://doc.0ptr.de/liblogcpp/annotated.html)
* Packages can be found for ArchLinux in [Arch User Repository](https://aur.archlinux.org/liblogcpp) and with QString support enabled [here](https://aur.archlinux.org/liblogcpp-qt).
* How to use it is documented lower on this page.

If you wrote additional datastructures or functions and you think it could be useful within this library: You are welcome to create a pull request or contact me ( lauseb644 _at_ gmail _dot_ com ).

Since v1.8.0 LibLogC++ supports the most log features except for colorized terminal output on windows. More features can be requested through issues on [GitHub](https://github.com/nullptrT/liblogcpp)


#### Currently supported features

* Creating loggers and simply writing to them via `operator<<`.
* A global default logger (stdlog), which manages a console log and a file log. Both can be enabled and disabled.
* Logging by severity. There is a fully functional default severity_logger, but you also can use your own severities.
* Using formatters from <iomanip>
* Specifying a streambuffer to log to (like ofstream->rdbuf() or similar; defaults to std::cout.rdbuf).
* A channel logger, also usable via `operator<<`
* Assertion-functions aviable via the header `assert.hpp`
* Optionally execute a function on critical warnings or throw a `logcpp::critical_exception` (from `log_exception.hpp`).
* Logging the scope where the logstream comes from (identified by `__FILE__` and `__LINE__`) by simply inserting `SCOPE` into a log stream.
* Documentation
* A `find_package` module for cmake
* Support for QString
* Packaging scripts for Arch Linux


## Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/nullptrT/liblogcpp.git
 % mkdir liblogcpp/build # or some other build directory
 % cd liblogcpp/build
 % cmake .. # You may add CMake options here (see below)
 % make
```

On windows you may use the `cmake-gui` or `qtcreator` to create build files for MSVC 2015 or later.


#### CMake options

Additionally to the default options CMake currently offers the following options (can be specified with `-DOPTION=ON`):

* `LOGCPP_SHARED`: Enables building a shared library `liblogcpp.so`. Not using this option builds a static `liblogcpp.a` by default.
* `LOGCPP_DESTDIR`: Where are the files installed to. Defaults to `CMAKE_INSTALL_PREFIX` (`/usr` on UNIX and `c:/Program Files` on WIN32)
* `LOGCPP_HEADER_INSTALL_DIR`: Can be set to control, where headers are installed. Defaults to `LOGCPP_DESTDIR/include/liblogcpp`.
* `LOGCPP_LIB_INSTALL_DIR`: Can be set to control where the library is installed. Defaults to `LOGCPP_DESTDIR/lib`.
* `LOGCPP_INSTALL_LIBS`: Enables targets for installation of library files. Because it is useful not to install the library (e.g. when used as submodule of a project) this defaults to off. If enabled, it installs all headers to `LOGCPP_HEADER_INSTALL_DIR` and the library to `LOGCPP_LIB_INSTALL_DIR`
* `BUILD_LOGCPP_TEST`: Build a simple main runtime that demonstrates current features of liblogcpp.

#### Compiler options / Config variables

You can define the following with your g++-compiler by `-DOPTION=1` or cmake's `add_definitions( -D$OPTION=1 )` function:

* `LOGCPP_LEAVE_SCOPE_DIRS_PREFIX`: Does not strip everything except the filename from SCOPE (like `/path/to/` in `/path/to/compilation.cpp`) since that defaults to the path in the build environment. Defaults to true.

As an example you could write a `logging.hpp` header like this:

```c++
#include <liblogcpp/log.hpp>			/* If you want to use the global logger
											(like stdlog << logcpp::warning << "some text" << logcpp::endrec) */
#include <liblogcpp/logcpp-qt.hpp>      /* If you want to pass QStrings to your loggers */

namespace myNamespace {
namespace log = logcpp;
} // namespace myNamespace
```

and for additional version checking without CMake you could have a `logging.cpp` file compiled like this:

```c++
#include <liblogcpp/logcppversion.hpp>

#if LIBLOGCPP_VERSION < 10903
#error LibLogC++ needs to be at least at version 1.9.3
#else
#pragma message ("Found LibLogC++ at required version 1.9.3 or more")
#endif
```

#### Requirements

* cmake>=3.0
* a c++ compiler (tested for gcc)
* doxygen (optional for building the [html documentation](https://doc.0ptr.de/liblogcpp/))


## Use with CMake


The included `LibLogCPPConfig.cmake` module enables you to use `find_package(LibLogCPP >= 1.6)` in CMake:
* `LIBLOGCPP_INCLUDE_DIR`: The directory, where the headers are located in `liblogcpp/` (usually `/usr/include`)
* `LIBLOGCPP_LIBRARY`: The static library you can link into your program. It's only useful, if you use `stdlog`
* `LIBLOGCPP_VERSION_STRING`: The current version of liblogcpp.


## License:

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

* Copyright (C) 2015 Linux Gruppe IRB, TU Dortmund <linux@irb.cs.tu-dortmund.de>
* Copyright (C) 2015-2017 Sebastian Lau <lauseb644@gmail.com>


## Usage

The included file `main.cpp` can be used and compiled as an additional example for its usage. For a more detailed reference, please read the following short documentation.

For most simple cases, you may use the globallog by including `logcpp/log.hpp` to your file.
This will give you the ability to use stdlog, which offers you a console logger and a file logger. You can write to an enabled logger by using `<<` once:
```c++
#include <log.hpp>
stdlog.set_logfile("/path/to/file");   // Without this line, stdlog would log to ./globallog.log
stdlog.enable_file_log();              // Without this line, the file logger would not be called (default behaviour)
stdlog << logcpp::warning << "A sample message to std::cout and /path/to/file" << logcpp::endrec
```

On the other hand you can create more loggers by simply passing a `std::streambuf` pointer to the constructor. If you omit this pointer, the logger will log to `std::cout`.

```c++
#include <logcpp/basic_log.hpp>

logcpp::logger lg; // Will be used in later examples, too
lg << "A sample message to std::cout with the use of an own logger object";
```

Note, that using such as `std::endl` is not supported and probably won't be because of its flush behaviour.
Instead one may use `logcpp::endl` for buffering a `"\n"` and `logcpp::endrec` to flush the buffer to whatever the buffer(s) point to and begin a new record.

For example
```c++
// ...
lg << "A sample message" << logcpp::endl << "A second message" << logcpp::endrec;
// ...
```
would print
```
A sample message
A second message
```
while
```c++
// ...
lg << "A sample message" << logcpp::endl;
// ...
```
would not print at all, because the logstream is not flushed with `logcpp::endrec`

#### Logging with severities

Simply include `logcpp/severity_logger.hpp` in your file or use the global logger from `logcpp/log.hpp`.
The usage is the same as with the simple logger, but you can do
```c++
#include <logcpp/severity_logger.hpp>

logcpp::severity_logger slogger(logcpp::verbose); // Will be used in later examples, too
slogger << "The standard severity defaults to logcpp::normal" << logcpp::endrec;
slogger << logcpp::verbose << "But it can be set to level logcpp::verbose by inserting logcpp::verbose into the stream" << logcpp::endrec;
slogger << "However, this is still a message with severity logcpp::verbose" << logcpp::endrec;
slogger << logcpp::debug << "Until changed to some other severity_level" << logcpp::endrec;
```
The maximal severity of a severity_logger defaults to `logcpp::normal`, but can be changed by passing a `logcpp::severity_level` to the constructor or invoking `lg->set_max_severity(logcpp::severity_level)`.
When using stdlog, you can also use `set_max_{console,file}_severity(logcpp::severity_level)` for controlling only one of them.
The severity_logger will also flush its stream on `logcpp::endrec`, but in case, the max severity level is less than the current severity (last severity inserted into stream), it just clears its internal buffer and does not log anything.
Assuming the max_severity of `lg` in the example above is `logcpp::verbose`, everything would get logged except the last line, which hast `logcpp::debug` as current `severity_level`.


#### Logging with channels

```c++
#include <logcpp/channel_log.hpp>
#include <logcpp/severity_logger.hpp>

std::ofstream* ofs = new std::ofstream( "./flog_test.log", std::ofstream::out | std::ofstream::app | std::ofstream::ate);
logcpp::severity_logger flog( ofs->rdbuf() );

logcpp::channellog< logcpp::severity_logger > ch; // Use your most common base type as template parameter
ch.add_channel( "file", flog );
ch.add_channel( "console", slogger );
ch["file"] << "A message to the file channel" << logcpp::endrec;
ch["console"] << "A message to the console channel" << logcpp::endrec;
```

#### QString and passing own types to loggers

In order to make liblogcpp not depend on `qt-core` there is a compatibility header `liblogcpp/logcpp-qt.hpp` shipped since v1.9.1, which has to be included in some file of your program (in addition to the regular library headers). This header enables the basic logging buffer to handle QString passed to it. You makes your program to be needed to be linked to `${Qt5Core_LIBRARIES}`!

If you want to make your own types be able to be passed to a logger you can look at `liblogcpp/logcpp-qt.hpp` for an example conversion function. Here is an example for your own compatibility header:

```c++
#include <liblogcpp/logstream.hpp>

struct A {
    std::string m_name;
    std::string m_description;
    A(std::string name, std::string description) : m_name(name), m_description(description)) {}
};

inline logstreambuf& operator<<(logstreambuf& out, const A& myClass) {
    out << myClass.name << "\n" << myClass.description << "\n";
    return out;
}
```

#### More features

* If you need simple assertions you can use the assertion header `assert.hpp`, which provides two functions:
```c++
#include <logcpp/assert.hpp>

// One assert function only logs on failure
logcpp::assert(false, slogger << logcpp::error << "This assertion evaluated false" << logcpp::endrec);
// The second one can have one message for failure and one for a successful evaluation
int num = 3;
logcpp::assert( num >= 3
              , slogger << logcpp::normal << "This assertion evaluated true" << logcpp::endrec
              , slogger << logcpp::error << "This assertion evaluated false" << logcpp::endrec );
```
If you need a more complex conditional evaluation, you have to use if-statements.
* You can use manipulators from `<iomanip>` like this (output: `002a`)
```c++
#include <logcpp/logmanip.hpp>

lg << std::setw(4) << std::setfill('0') << std::hex << 42 << logcpp::endrec;
```
* You can enable a timestamp at the beginning of each record with `enable_timestamp()`. You can disable it with `disable_timestamp()`. The file logger of stdlog has timestamps enabled by default. For controlling only one of the loggers in stdlog there are the functions `use_timestamps_{console,file}(bool)`.  If you need a timestamp in your log message, you can insert the `TIME` macro into any logger.
* You can pass a function to all instances of `severity_log`. If this function is not a `nullptr`, it will be executed at the end of a record with a severity value of 1. For a better usability its a `nullptr` by default, but it can be enabled with `set_critical_log_function(void(*crit_f)(void))` on each severity_log. A useful function could be `std::abort`.
* The color functionality is only available on UNIX and all functions are stripped from files on WIN32. `basic_log` only logs colors, if the sink is a terminal. If you want to log some text in colors, you can do something like this:
```c++
// ...
#include <logcpp/color_feature.hpp>

lg << logcpp::col_red << "This text would be logged in red." << logcpp::endrec;
lg << "Each 'logcpp::endrec' resets the current style, so this would be logged normal";
lg << logcpp::ctl_background << logcpp::col_yellow << "[Yellow Background] By using the ctl_* you can control specific parts of your record.[/Yellow Background] " << logcpp::ctl_reset_all << logcpp::sty_bold << "This is logged uncolored in bold." << logcpp::endrec
```
Note that some background operations may cause undefined results (like `lg << logcpp::ctl_background << logcpp::sty_bold`), so use them carefully.


### Creating own logger and severity classes

Simply inherit from `basic_log` (in `logcpp/basic_log.hpp`), `severity_logger` (in `logcpp/severity_logger.hpp`) or `severity_log< typename severity_t >` (in `logcpp/severity_log.hpp`), where `severity_t` is an severity class type like `DefaultSeverity` which defined in `logcpp/severity_default.hpp`.

When defining an own `severity_t`, keep in mind, that backend (`severity_log`) threats the enum value `0` as `off` (this logger won't create any logs until its max_severity isn't changed to a higher value) and the enum value `1` will call the critical function at the end of a record, if it is enabled. If you want to define your own severity, simply inherit from `AbstractSeverity< severity_t >` (defined in `logcpp/severity.hpp`) like done in `severity_default.hpp`. At least your enum type `severity_t` has to have a specified array defining the severity names in your inheriting class (more on defining own severity classes have a look at `severity_default.cpp`).

For an example of inheritance from `basic_log` or `severity_log` and nessecary template specializations see `severity_log.hpp` and `severity_logger.hpp`.
