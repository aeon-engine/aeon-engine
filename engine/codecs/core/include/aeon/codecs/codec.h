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

#include <aeon/resources/resource_encoding.h>
#include <aeon/common/exception.h>
#include <memory>

namespace aeon
{
namespace codecs
{

// codec
DEFINE_EXCEPTION_OBJECT(codec_exception, common::exception, "Generic Codec exception.");

class codec
{
public:
    codec() = default;
    virtual ~codec() = default;

    codec(const codec &) noexcept = delete;
    auto operator=(const codec &) noexcept -> codec & = delete;

    codec(codec &&) noexcept = default;
    auto operator=(codec &&) noexcept -> codec & = default;
};

class codec_factory
{
public:
    codec_factory() = default;
    virtual ~codec_factory() = default;

    codec_factory(const codec_factory &) noexcept = delete;
    auto operator=(const codec_factory &) noexcept -> codec_factory & = delete;

    codec_factory(codec_factory &&) noexcept = default;
    auto operator=(codec_factory &&) noexcept -> codec_factory & = default;

    virtual auto create() const -> std::unique_ptr<codec> = 0;
    virtual auto get_encoding() const -> resources::resource_encoding = 0;
};

} // namespace codecs
} // namespace aeon
