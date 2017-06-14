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

#include <aeon/codecs/codec.h>
#include <aeon/resources/providers/resource_provider.h>
#include <memory>

namespace aeon
{
namespace codecs
{

template <typename T>
class basic_codec : public codec
{
public:
    basic_codec() = default;
    virtual ~basic_codec() = default;

    virtual auto decode(const std::unique_ptr<resources::resource_provider> &provider) const -> std::unique_ptr<T> = 0;
    virtual void encode(std::shared_ptr<T> source,
                        const std::unique_ptr<resources::resource_provider> &destination) const = 0;
};

template <typename T>
class basic_codec_factory : public codec_factory
{
public:
    explicit basic_codec_factory(const resources::resource_encoding &encoding);
    virtual ~basic_codec_factory() = default;

    auto create() const -> std::unique_ptr<codec> override;
    auto get_encoding() const -> resources::resource_encoding override;

private:
    resources::resource_encoding encoding_;
};

template <typename T>
basic_codec_factory<T>::basic_codec_factory(const resources::resource_encoding &encoding)
    : encoding_(encoding)
{
}

template <typename T>
inline auto basic_codec_factory<T>::create() const -> std::unique_ptr<codec>
{
    return std::unique_ptr<codec>(std::make_unique<T>());
}

template <typename T>
inline auto basic_codec_factory<T>::get_encoding() const -> resources::resource_encoding
{
    return encoding_;
}

} // namespace codecs
} // namespace aeon
