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

#include <aeon/codecs/codec_manager.h>

namespace aeon
{
namespace codecs
{

codec_manager::codec_manager()
    : logger_(common::logger::get_singleton(), "Codecs::CodecManager")
{
}

codec_manager::~codec_manager() = default;

void codec_manager::register_codec(std::unique_ptr<codec_factory> &&factory)
{
    auto encoding = factory->get_encoding();
    register_codec(std::move(factory), encoding);
}

void codec_manager::register_codec(std::unique_ptr<codec_factory> &&factory,
                                   const resources::resource_encoding &encoding)
{
    AEON_LOG_DEBUG(logger_) << "Registering codec: " << encoding << std::endl;
    codecs_[encoding] = std::move(factory);
}

} // namespace codecs
} // namespace aeon
