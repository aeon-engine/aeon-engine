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

#include <aeon/mono.h>

namespace aeon
{
namespace mono
{

mono_gchandle::mono_gchandle()
    : handle_(0)
{
}

mono_gchandle::mono_gchandle(MonoObject *object)
    : handle_(0)
{
    handle_ = mono_gchandle_new(object, 1);
}

mono_gchandle::mono_gchandle(MonoString *object)
    : handle_(0)
{
    handle_ = mono_gchandle_new(reinterpret_cast<MonoObject *>(object), 1);
}

mono_gchandle::~mono_gchandle()
{
    if (handle_ != 0)
        mono_gchandle_free(handle_);
}

mono_gchandle::mono_gchandle(mono_gchandle &&o)
    : handle_(o.handle_)
{
}

mono_gchandle &mono_gchandle::operator=(mono_gchandle &&o)
{
    handle_ = o.handle_;
    return *this;
}

} // namespace mono
} // namespace aeon
