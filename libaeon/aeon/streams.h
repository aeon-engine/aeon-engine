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
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <vector>
#include <fstream>
#include <array>
#include <iostream>
#include <type_traits>
#include <memory>
#include <string>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/utility/noncopyable.h>
#include <aeon/platform.h>
#include <aeon/streams/config.h>
#include <aeon/streams/access_mode_mixin.h>
#include <aeon/streams/stream_name_mixin.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/file_stream.h>
#include <aeon/streams/circular_buffer_stream.h>
#include <aeon/streams/io_stream_colors_mixin.h>
#include <aeon/streams/io_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
