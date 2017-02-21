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
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <array>
#include <cassert>
#include <cctype>
#include <chrono>
#include <exception>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <future>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/streams.h>
#include <aeon/utility/asynchronizer.h>
#include <aeon/utility/noncopyable.h>
#include <aeon/utility/singleton.h>
#include <aeon/utility/string_traits.h>
#include <aeon/utility/configfile.h>
#include <aeon/utility/hexdump.h>
#include <aeon/utility/endianness.h>
#include <aeon/utility/timer.h>
#include <aeon/utility/optional.h>
#include <aeon/utility/linear_map.h>
#include <aeon/utility/variant.h>
#include <aeon/utility/listener_subject.h>
#include <aeon/utility/string.h>
#include <aeon/utility/dispatcher.h>
#include <aeon/utility/signals.h>
#include <aeon/utility/parameters.h>
#include <aeon/utility/parallelizer.h>
#include <aeon/utility/container.h>
#include <aeon/utility/literals.h>
#include <aeon/utility/bitflags.h>
