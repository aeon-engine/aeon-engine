Aeon Game Engine
==============

Changelog
--------------
The changelog can be found [here](CHANGELOG.md). This changelog describes high
level changes made to the engine between release versions. For more detailed
information please refer to the GIT commit log.

Copyright notice
--------------
All code in this repository is confidential.
All Rights Reserved.

ROBIN DEGEN; CONFIDENTIAL

2012 - 2016 Robin Degen
All Rights Reserved.

NOTICE:  All information contained herein is, and remains the property of
Robin Degen and its suppliers, if any. The intellectual and technical
concepts contained herein are proprietary to Robin Degen and its suppliers
and may be covered by U.S. and Foreign Patents, patents in process, and are
protected by trade secret or copyright law. Dissemination of this
information or reproduction of this material is strictly forbidden unless
prior written permission is obtained from Robin Degen.

Libraries
--------------
Currently Aeon uses the following libraries:

- libAeon
- Glew
- GLFW
- GLM
- libpng
- zlib
- Google Test

All dependencies are added as git submodules. No external libraries should be required
in order to build; other then standard compiler or OS provided libraries.

Compiling
--------------

- Clone this repository recursively.
- Run either bootstrap.sh (osx/linux) or bootstrap.cmd (windows)
- Build from the created build folder (build or vs_build)
- ???
- Profit!

Code style
--------------
A detailed description of code style is yet to be written. Please follow the 
style as established in the existing code. When in doubt, ask Robin Degen.

In short:

- Prefer C++14 standards above boost or any other library
- 4 spaces, no tabs.
- No CamelCase. Variables and types must be named_like_this.
- 120 character maximum line length.
- No compiler or static analysis warnings. Ever.

The following comment MUST be at the top of all source files, and must be kept
up to date with the version as written in this readme file.

NOTICE:
If any file has this comment missing or of it is different from what is written 
below, the text below will always apply above everything else.

	/*
	 * ROBIN DEGEN; CONFIDENTIAL
	 *
	 * 2012 - 2016 Robin Degen
	 * All Rights Reserved.
	 *
	 * NOTICE:  All information contained herein is, and remains the property of
	 * Robin Degen and its suppliers, if any. The intellectual and technical
	 * concepts contained herein are proprietary to Robin Degen and its suppliers
	 * and may be covered by U.S. and Foreign Patents, patents in process, and are
	 * protected by trade secret or copyright law. Dissemination of this
	 * information or reproduction of this material is strictly forbidden unless
	 * prior written permission is obtained from Robin Degen.
	 */
