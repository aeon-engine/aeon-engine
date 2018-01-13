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

#pragma once

#include <aeon/codecs/basic_codec.h>
#include <aeon/resources/image.h>
#include <aeon/logger/logger.h>

namespace aeon
{
namespace codecs
{

DEFINE_EXCEPTION_OBJECT(codec_dds_decode_exception, codec_exception, "Error while decoding DDS image resource.");
DEFINE_EXCEPTION_OBJECT(codec_dds_encode_exception, codec_exception, "Error while encoding DDS image resource.");

class image_codec_dds : public basic_codec<resources::image>
{
public:
    image_codec_dds();
    virtual ~image_codec_dds();

    auto decode(const std::unique_ptr<resources::resource_provider> &provider) const
        -> std::unique_ptr<resources::image> override;
    void encode(std::shared_ptr<resources::image> source,
                const std::unique_ptr<resources::resource_provider> &destination) const override;

private:
    auto convert_fourcc_to_fixel_format(const std::uint32_t fourcc) const -> data::image::pixel_format;

    mutable logger::logger logger_;
};

} // namespace codecs
} // namespace aeon
