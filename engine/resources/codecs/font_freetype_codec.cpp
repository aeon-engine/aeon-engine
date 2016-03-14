/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <aeon/utility.h>
#include <resources/resource_manager.h>
#include <resources/codecs/font_freetype_codec.h>
#include <common/buffer.h>
#include <memory>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace aeon
{
namespace resources
{

class freetype_library
{
public:
    freetype_library()
    {
        if (FT_Init_FreeType(&library_))
        {
            throw std::runtime_error("Freetype failed to initialize");
        }
    }

    ~freetype_library()
    {
        if (FT_Done_FreeType(library_))
        {
            throw std::runtime_error("Freetype failed to cleanup.");
        }
    }

    FT_Library &get_library() const
    {
        return library_;
    }

private:
    static FT_Library library_;
};

font_codec_freetype::font_codec_freetype()
    : logger_(common::logger::get_singleton(), "Resources::FontFreetypeCodec")
{
}

font_ptr font_codec_freetype::decode(resource_manager &parent, font_resource_wrapper_ptr wrapper)
{
    common::buffer_u8 input;
    wrapper->read_raw(input);

    return nullptr;
}

resource_encoding font_codec_freetype::get_codec_type() const
{
    return resource_encoding::freetype_font;
}

} // namespace resources
} // namespace aeon
