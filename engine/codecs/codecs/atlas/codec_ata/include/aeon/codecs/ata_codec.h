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
#include <aeon/resources/atlas.h>
#include <aeon/logger/logger.h>
#include <aeon/common/types/rectangle.h>
#include <string>

namespace aeon::codecs
{

DEFINE_EXCEPTION_OBJECT(atlas_codec_decode_exception, codec_exception, "Error while decoding atlas resource.");
DEFINE_EXCEPTION_OBJECT(atlas_codec_encode_exception, codec_exception, "Error while encoding atlas resource.");

class atlas_codec_ata : public basic_codec<resources::atlas>
{
public:
    atlas_codec_ata();
    virtual ~atlas_codec_ata();

    auto decode(const std::unique_ptr<resources::resource_provider> &provider) const
        -> std::unique_ptr<resources::atlas> override;
    void encode(std::shared_ptr<resources::atlas> source,
                const std::unique_ptr<resources::resource_provider> &destination) const override;

private:
    auto __atlas_string_to_data(const std::string &str) const -> common::types::rectangle<float>;

    logger::logger logger_;
};

} // namespace aeon::codecs
