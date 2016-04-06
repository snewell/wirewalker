# Wirewalker
Wirewalker is a C++ implementation of [OpenDOF][opendof].  Wirewalker is
available under the two-clause BSD license, a highly permissive license.

Wirewalker is still very early in development but is intended to be highly
configurable.  The goal is to permit a developer to create a DOF system with
exactly the protocols they want to support and, when appropriate, change the
behavior of existing protocols.

## Building
Wirewalker is built using [CMake][cmake].  CMake supports numerous options but
the simplest usage is:

1. `mkdir some/build/dir`
2. (from build dir) `cmake /path/to/wirewalker/src`
3. `make`

Wirewalker is written using C++14 and assumes the compiler used by CMake will
be configured as required.  If the C++ compiler CMake uses does not support
C++14 *by default* you'll need to add the necessary flags during configuration
(e.g,. `cmake CMAKE_CXX_FLAGS=-std=c++14 /path/to/wirewalker/src`).

### Tests
Unit tests are available if [cppunit][cppunit] is installed.  CMake will add a
`test` target so they can be run (`make test`).

[cmake]: http://cmake.org/ "CMake"
[cppunit]: https://sourceforge.net/projects/cppunit/ "cppunit"
[opendof]: http://opendof.org/ "The OpenDOF Project"
