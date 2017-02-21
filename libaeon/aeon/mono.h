/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

/******************************************************************************/
/* Standard headers                                                           */
/******************************************************************************/
#include <string>
#include <vector>
#include <cstdint>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/utility.h>
#include <aeon/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

/******************************************************************************/
/* Mono headers                                                               */
/******************************************************************************/
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_gchandle.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_object.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>
