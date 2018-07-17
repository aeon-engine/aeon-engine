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

#include <aeon/codecs/png_codec.h>
#include <aeon/common/logger.h>
#include <aeon/logger/logger.h>
#include <png.h>

namespace aeon
{
namespace codecs
{

class png_structs
{
public:
    explicit png_structs(logger::logger &logger);
    virtual ~png_structs();

    png_structs(const png_structs &) noexcept = delete;
    auto operator=(const png_structs &) noexcept -> png_structs & = delete;

    png_structs(png_structs &&) noexcept = default;
    auto operator=(png_structs &&) noexcept -> png_structs & = default;

    auto png_ptr() const;
    auto info_ptr() const;
    auto end_info() const;

protected:
    auto create_info_struct() const -> png_infop;

    logger::logger &logger_;
    png_structp png_ptr_;
    png_infop info_ptr_;
    png_infop end_info_;
};

inline png_structs::png_structs(logger::logger &logger)
    : logger_(logger)
    , png_ptr_(nullptr)
    , info_ptr_(nullptr)
    , end_info_(nullptr)
{
}

inline png_structs::~png_structs()
{
    png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
    png_ptr_ = nullptr;
    info_ptr_ = nullptr;
    end_info_ = nullptr;
}

inline auto png_structs::png_ptr() const
{
    return png_ptr_;
}

inline auto png_structs::info_ptr() const
{
    return info_ptr_;
}

inline auto png_structs::end_info() const
{
    return end_info_;
}

inline auto png_structs::create_info_struct() const -> png_infop
{
    // Create png info struct
    auto info_ptr = png_create_info_struct(png_ptr_);

    if (!info_ptr)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Could not create info struct." << std::endl;
        throw codec_png_codec_exception();
    }

    return info_ptr;
}

} // namespace codecs
} // namespace aeon
