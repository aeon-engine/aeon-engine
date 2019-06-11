/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/codecs/png_codec.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/common/logger.h>
#include <png.h>
#include <array>

namespace aeon::codecs
{

image_codec_png::image_codec_png()
    : logger_(common::logger::get_singleton(), "Codecs::PNGCodec")
{
}

auto image_codec_png::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::image>
{
    AEON_LOG_DEBUG(logger_) << "Decoding PNG image." << std::endl;

    auto img = imaging::file::png::load(provider->get_stream());
    return std::make_unique<resources::image>(std::move(img));
}

void image_codec_png::encode(std::shared_ptr<resources::image> source,
                             const std::unique_ptr<resources::resource_provider> &destination) const
{
    AEON_LOG_DEBUG(logger_) << "Encoding PNG image." << std::endl;
    imaging::file::png::save(source->get_data(), destination->get_stream());
}

} // namespace aeon::codecs
