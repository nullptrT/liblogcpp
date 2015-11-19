# liblogcpp
##### A simple, but highly customizable and intuitive LGPL library for logging in C++.
###### v1.6.0

This library aims to be simple, but highly usable and customizable without having a bunch of other unused dependencies, libraries or code.
It is a simple and intuitive frontend to libstdc++ turning it into a fully featured and easy to use general purpose logger.

I know, there is the fantastic Boost.Log library, supporting all features one could need for logging to something. If you can't solve your demands by using this library or writing simple additional datastructures or deriving classes for this library, you probably should go here: http://www.boost.org/doc/libs/release/libs/log/ .

If you wrote additional datastructures or functions and you think it could be useful within this library: You are welcome to create a pull request or contact me ( lauseb644 _at_ gmail _dot_ com ).


#### Currently supported features

* Creating loggers and simply writing to them via `operator<<`.
* A global default logger (stdlog), which manages a console log and a file log. Both can be enabled and disabled.
* Logging by severity. There is a fully functional default severity_logger, but you also can use your own severities.
* Using formatters from <iomanip>
* Specifying a streambuffer to log to (like ofstream->rdbuf() or similar; defaults to std::cout.rdbuf).
* Optionally execute a function on critical warnings or throw a `logcpp::critical_exception` (from `log_exception.hpp`).
* Logging the scope where the logstream comes from (identified by `__FILE__` and `__LINE__`) by simply inserting `SCOPE` into a log stream.
* Timestamp support

* A `find_package` module for cmake
* Packaging scripts for Arch Linux

#### Features for future releases

* Colorized output
* Later on: A global channel logger, also usable via `operator<<`

## Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/gS644/.git
 % mkdir liblogcpp/build # or some other build directory
 % cd /path/to/builddir
 % cmake /path/to/cloned/directory
 % make
```

Additionally to the default options CMake currently offers the following options (can be specified with `-DOPTION=ON`):

* `INSTALL_LIBS`: Enables targets for installation of library files. Because it is useful not to install the library (e.g. when used as submodule of a project) this defaults to off.
* `BUILD_LOGCPP_TEST`: Build a simple main runtime that demonstrates current features of liblogcpp.

#### Packages

Currently there is a package in the Arch Linux User Repository under https://aur.archlinux.org/packages/liblogcpp/ .
More distributions may follow or be submitted.

#### Requirements

* cmake>=2.8
* a c++ compiler (tested for gcc)


## Use with CMake


The included `LibLogCPPConfig.cmake` module enables you to use `find_package(LibLogCPP >= 1.6)` in CMake:
* `LibLogCPP_INCLUDE_DIR`: The directory, where the headers are located in `liblogcpp/` (usually `/usr/include`)
* `LibLogCPP_LIBRARY`: The static library you can link into your program. It's only useful, if you use `stdlog`
* `LibLogCPP_VERSION_STRING`: The current version of liblogcpp.


## Usage

At the moment, the library is under active development. The included file `main.cpp` can be used and compiled as an additional example for its usage. For a more detailed reference, please read the following short documentation.

However, you can use it by including `log.hpp` to your file.
This will give you the ability to use stdlog, which offers you a console logger and a file logger. You can write to an enabled logger by using `<<` once:
```c++
#include <log.hpp>
stdlog.set_logfile("/path/to/file");   // Without this line, stdlog would log to ./globallog.log
stdlog.enable_file_log();              // Without this line, the file logger would not be called (default behaviour)
stdlog << "A sample message to std::cout and /path/to/file" << logcpp::endrec
```

On the other hand you can create more loggers by simply passing a `std::streambuf` pointer to the constructor. If you omit this pointer, the logger will log to `std::cout`.

```c++
#include <basic_log.hpp>

logcpp::logger lg;
lg << "A sample message to std::cout with the use of an own logger object";
```

Note, that using such as `std::endl` is not supported and probably won't be because of its flush behaviour.
Instead one may use `logcpp::endl` for buffering a `"\n"` and `logcpp::endrec` to flush the buffer to whatever the buffer(s) point to and begin a new record.

For example
```c++
lg << "A sample message" << logcpp::endl << "A second message" << logcpp::endrec;
```
would print
```
A sample message
A second message
```
while
```c++
lg << "A sample message" << logcpp::endl;
```
would not print at all, because the logstream is not flushed with `logcpp::endrec`

#### Logging with severities

Simply include `severity_logger.hpp` in your file or use the global logger from `log.hpp`.
The usage is the same as with the simple logger, but you can do
```c++
lg << "The standard severity defaults to logcpp::normal" << logcpp::endrec;
lg << logcpp::verbose << "But it can be set to level logcpp::verbose by inserting logcpp::verbose into the stream" << logcpp::endrec;
lg << "However, this is still a message with severity logcpp::verbose" << logcpp::endrec;
lg << logcpp::debug << "Until changed to some other severity_level" << logcpp::endrec;
```
The maximal severity of a severity_logger defaults to `logcpp::normal`, but can be changed by passing a `logcpp::severity_level` to the constructor or invoking `lg->set_max_severity(logcpp::severity_level)`.
When using stdlog, you can also use `set_max_{console,file}_severity(logcpp::severity_level)` for controlling only one of them.
The severity_logger will also flush its stream on `logcpp::endrec`, but in case, the max severity level is less than the current severity (last severity inserted into stream), it just clears its internal buffer and does not log anything.
Assuming the max_severity of `lg` in the example above is `logcpp::verbose`, everything would get logged except the last line, which hast `logcpp::debug` as current `severity_level`.


#### More features

* You can use manipulators from `<iomanip>` like this (output: `002a`)
```c++
#include <logmanip.hpp>
...
lg << std::setw(4) << std::setfill('0') << std::hex << 42 << logcpp::endrec;
```
* You can enable a timestamp at the beginning of each record with `enable_timestamp()`. You can disable it with `disable_timestamp()`. The file logger of stdlog has timestamps enabled by default. For controlling only one of the loggers in stdlog there are the functions `use_timestamps_{console,file}(bool)`.  If you need a timestamp in your log message, you can insert the `TIME` macro into any logger.
* You can pass a function to all instances of `severity_log`. If this function is not a `nullptr`, it will be executed at the end of a record with a severity value of 1. For a better usability its a `nullptr` by default, but it can be enabled with `set_critical_log_function(void(*crit_f)(void))` on each severity_log. A useful function could be `std::abort`.


### Creating own loggers

Simply inherit from `basic_log` (in `basic_log.hpp`) or `severity_log< typename severity_t, const std::string (*severity_name)(severity_t), const uint (*max_name_length)(void) = nullptr >`, where `severity_t` is an enum type of your own severity and `severity_name` is a corresponding function taking your `severity_t` and returning a stream-qualified string.
If you want your severities aligned when printed, you also have to provide a function which returns the number of characters in the longest severity name. Otherwise the default option 'noalign' is used.

When defining an own `severity_t`, keep in mind, that backend (`severity_log`) treats the enum value `0` as `off` (this logger won't create any logs until its max_severity isn't changed to a higher value) and the enum value `1` will call the critical function at the end of a record, if it is enabled.

For an example of inheritance from `basic_log` or `severity_log` and nessecary template specializations see `severity_log.hpp` and `severity_logger.hpp`.

