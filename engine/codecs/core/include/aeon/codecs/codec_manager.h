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

#include <aeon/codecs/codec.h>
#include <aeon/codecs/basic_codec.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/common/exception.h>
#include <aeon/logger/logger.h>
#include <aeon/common/logger.h>
#include <map>
#include <memory>

namespace aeon::codecs
{

DEFINE_EXCEPTION_OBJECT(codec_manager_exception, common::exception, "Generic Codec Manager exception.");
DEFINE_EXCEPTION_OBJECT(codec_unknown_exception, codec_manager_exception, "Unknown Codec exception.");

class codec_manager
{
public:
    codec_manager();
    ~codec_manager();

    codec_manager(const codec_manager &) noexcept = delete;
    auto operator=(const codec_manager &) noexcept -> codec_manager & = delete;

    codec_manager(codec_manager &&) noexcept = default;
    auto operator=(codec_manager &&) noexcept -> codec_manager & = default;

    void register_codec(std::unique_ptr<codec_factory> &&factory);
    void register_codec(std::unique_ptr<codec_factory> &&factory, const resources::resource_encoding &encoding);

    auto create(const resources::resource_encoding &encoding);

    template <typename T>
    auto create_basic(const resources::resource_encoding &encoding);

private:
    logger::logger logger_;
    std::map<resources::resource_encoding, std::unique_ptr<codec_factory>> codecs_;
};

inline auto codec_manager::create(const resources::resource_encoding &encoding)
{
    auto result = codecs_.find(encoding);

    if (result == codecs_.end())
    {
        AEON_LOG_ERROR(logger_) << "Unknown codec: " << encoding << std::endl;
        throw codec_unknown_exception();
    }

    return result->second->create();
}

template <typename T>
inline auto codec_manager::create_basic(const resources::resource_encoding &encoding)
{
    auto codec = create(encoding);
    auto *basic_codec_ptr = &dynamic_cast<basic_codec<T> &>(*codec.get());
    codec.release();
    return std::unique_ptr<basic_codec<T>>(basic_codec_ptr);
}

} // namespace aeon::codecs
