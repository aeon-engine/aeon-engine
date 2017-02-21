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
#include <set>
#include <queue>
#include <memory>
#include <utility>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/utility.h>
#include <aeon/streams.h>

#include <aeon/logger/log_level.h>
#include <aeon/logger/log_sink.h>
#include <aeon/logger/base_backend.h>
#include <aeon/logger/simple_backend.h>
#include <aeon/logger/simple_sink_backend.h>
#include <aeon/logger/multithreaded_sink_backend.h>
#include <aeon/logger/logger.h>
#include <aeon/logger/stream_sink.h>
#include <aeon/logger/io_stream_sink.h>
