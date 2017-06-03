Aeon Game Engine [![Travis-CI](https://travis-ci.org/aeon-engine/aeon-engine.svg?branch=master)](https://travis-ci.org/aeon-engine/aeon-engine)
==============

Changelog
--------------
The changelog can be found [here](CHANGELOG.md). This changelog describes high
level changes made to the engine between release versions. For more detailed
information please refer to the GIT commit log.

Compiling
--------------

The Aeon Engine uses CMake for it's build system. Other than CMake, no additional
knowledge should be required to get up and running. There are various "bootstrap"
scripts in the root of the archive for convenience for getting up and running
quickly.

Libraries
--------------
Currently Aeon uses the following libraries:

- libAeon (general purpose C++14 library)
- Open Asset Import Library
- GLEW
- GLFW or SDL2 (depending on build configuration)
- GLM
- Google Test
- Json11
- libpng
- zlib

All dependencies are included in this repository for convenience.
No external libraries should be required in order to build;
other then standard compiler or OS/distribution provided libraries like OpenGL.

Code style
--------------
A detailed description of code style is yet to be written. Please follow the 
style as established in the existing code. When in doubt, ask the project's
maintainer: Robin Degen.

In short:

- Prefer C++14 standards above boost or any other library
- 4 spaces, no tabs.
- No CamelCase. Variables and types must be named_like_this.
- 120 character maximum line length.
- No compiler or static analysis warnings. Ever.

The following comment MUST be at the top of all source files, and must be kept
up to date with the version as written in this readme file.

License
--------------
The Aeon Library is released under the MIT license.

Copyright (c) 2012-2017 Robin Degen

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.