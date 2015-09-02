Aeon Game Engine
==============

Copyright notice
--------------
All code in this repository is confidential.
All Rights Reserved.

ROBIN DEGEN; CONFIDENTIAL

2012 - 2015 Robin Degen
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
Currently Aeon uses the following libraries and versions:

- libAeon (master)
- Open Asset Import Library (3.1.1)
- Boost (1.59)
- Glew (Git snapshot glew-1.10.0-138-g9e3e40d)
- GLFW (3.1.1)
- GLM (0.9.7.0)
- libpng (1.6.18)
- zlib (1.2.8)
- libCurl (Git snapshot curl-7_44_0-57-g4963948, needed by libAeon)

Precompiled libraries are in Gitlab. They can be cloned from here:

- http://git.robindegen.nl/gitblit/r/binary/osx_clang.git (Apple Clang 6.4, OSX 10.10)
- http://git.robindegen.nl/gitblit/r/binary/win64_vs2015.git (Visual Studio 2015, Windows 64 bit)

Compiling
--------------

- Clone of the above mentioned precompiled library repositories.
- Create an environment variable AEON_LIBRARIES_PATH that points to this repository
- Run either bootstrap.sh (osx/linux) or bootstrap.cmd (windows).

Code style
--------------
A detailed description of code style is yet to be written. Please follow the 
style as established in the existing code. When in doubt, ask Robin Degen.

In short:

- Prefer C++11 standards above boost or any other library
- 4 spaces, no tabs.
- No CamelCase. Variables and types must be named_like_this.
- 80 character maximum line length.
- No compiler or static analysis warnings. Ever.

The following comment MUST be at the top of all source files, and must be kept
up to date with the version as written in this readme file.

NOTICE:
If any file has this comment missing or of it is different from what is written 
below, the text below will always apply above everything else.

	/*
	 * ROBIN DEGEN; CONFIDENTIAL
	 *
	 * 2012 - 2015 Robin Degen
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
