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

#include <aeon/codecs/png_structs.h>

namespace aeon
{
namespace codecs
{

class png_read_structs : public png_structs
{
public:
    explicit png_read_structs(logger::logger &logger);
    virtual ~png_read_structs();

    png_read_structs(png_read_structs &&o) = default;
    auto operator=(png_read_structs &&other) -> png_read_structs & = default;

private:
    void create_read_struct();
};

inline png_read_structs::png_read_structs(logger::logger &logger)
    : png_structs(logger)
{
    create_read_struct();

    // Create png info struct
    info_ptr_ = create_info_struct();

    // Create png end info struct
    end_info_ = create_info_struct();
}

inline png_read_structs::~png_read_structs()
{
    png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
}

inline void png_read_structs::create_read_struct()
{
    png_ptr_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (!png_ptr_)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Could not create read struct." << std::endl;
        throw codec_png_decode_exception();
    }
}

} // namespace codecs
} // namespace aeon
