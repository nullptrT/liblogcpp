# liblogcpp
##### A simple, but highly customizable and intuitive LGPL library for logging in C++.
###### v0.0.1a

So this library aims to be simple, but highly usable and customizable without having a bunch of other unused dependencies, libraries or code.
It is a simple and intuitive frontend to libstdc++ turning it into a fully featured and easy to use general purpose logger.

I know, there is the fantastic Boost.Log library, supporting all features one could need for logging to something. If you can't solve your demands by using this library or writing simple additional datastructures or deriving classes for this library, you probably should go here: http://www.boost.org/doc/libs/release/libs/log/ .

If you wrote additional datastructures or functions and you think it could be useful within this library: You are welcome to create a pull request or contact me.


#### Currently supported features

* Creating loggers and simply writing to them via `operator<<`.
* Specifying a streambuffer to log to (like ofstream.rdbuf() or similar; defaults to std::cout).
* Logging the scope where the logstream comes from (identified by `__FILE__` and `__LINE__`) by simply inserting `SCOPE` into a log stream.
* Logging by severity. There is a fully functional default severity_logger, but you also can use your own severities.

#### Features for future releases

* A global default logger, which manages a console log and a file log. Both can be en- and disabled.
* Using formatters <iomanip>
* Colorized output
* Later on: A global channel logger, also usable via `operator<<`


## Usage

At the moment, the library is under active development has no stable release.

However, you can use it by including `logger.hpp` to your file.
This will give you the ability to create a `logger` object or a `file_logger` object and simply write to it:

```c++
#include <logger.hpp>

log::logger lg;
lg << "A sample message";
```

Note, that using such as `std::endl` or `std::setw` is not supported at the moment.
Instead one may use `log::endl` for buffering a `"\n"` and `log::endrec` to flush the buffer to whatever the buffer(s) point to and begin a new record.

For example
```c++
lg << "A sample message" << log::endl << "A second message" << log::endrec;
```
would print
```
A sample message
A second message
```
while
```c++
lg << "A sample message" << log::endl;
```
would not print at all, because the logstream is not flushed with `log::endrec`

#### Logging with severities

Simply include `severity_logger.hpp` in your file.
The usage is the same as with the simple logger, but you can do
```c++
lg << "The standard severity defaults to log::normal" << log::endrec;
lg << log::verbose << "But it can be set to level log::verbose by inserting log::verbose into the stream" << log::endrec;
lg << "However, this is still a message with severity log::verbose" << log::endrec;
lg << log::debug << "Until changed to some other severity_level" << log::endrec;
```
The maximal severity of a severity_logger defaults to `log::normal`, but can be changed by passing a `log::severity_level` to the constructor or invoking `lg->set_max_severity(log::severity_level)`.
The severity_logger will also flush its stream on `log::endrec`, but in case, the max severity level is less than the current severity (last severity inserted into stream), it just clears its internal buffer and does not log anything.
Assuming the max_severity of `lg` in the example above is `log::verbose`, everything would get logged except the last line, which hast `log::debug` as current `severity_level`.

The avaiable


### Creating own loggers

Simply inherit from `basic_log` (in `basic_log.hpp`) or `severity_log< typename severity_t, const std::string (*severity_name)(severity_t) >`, where `severity_t` is an enum type of your own severity and `severity_name` is a corresponding function taking your `severity_t` and returning a stream-qualified string.

When defining an own `severity_t`, keep in mind, that backend (`severity_log`) treats the enum value `0` as `off` (this logger won't create any logs until its max_severity isn't changed to a higher value).

As example for and example of inheritance from `basic_log` or `severity_log` and nessecary template specializations see `severity_log.hpp` and `severity_logger.hpp`.

