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

#include <aeon/resources/resource_manager.h>
#include <aeon/resources/wrappers/resource_wrapper.h>
#include <aeon/resources/providers/resource_provider.h>

namespace aeon
{
namespace resources
{

resource_wrapper::resource_wrapper(resource_manager &parent, const std::string &path,
                                   const std::weak_ptr<resource_provider> &provider)
    : logger_(common::logger::get_singleton(), "Resources::ResourceWrapper")
    , parent_(parent)
    , path_(path)
    , provider_(provider)
    , encoding_(resource_encoding::unknown)
{
    if (auto p = provider.lock())
    {
        encoding_ = p->get_encoding(path);
    }
}

auto resource_wrapper::get_type() const -> resource_type
{
    return parent_.get_codec_manager().get_resource_type_by_encoding(encoding_);
}

void resource_wrapper::read_raw(std::vector<std::uint8_t> &buffer) const
{
    auto p = provider_.lock();

    if (!p)
    {
        AEON_LOG_FATAL(logger_) << "Failed to read resource at " << path_ << ". Provider not available." << std::endl;
        throw resource_closed_exception();
    }

    p->read(path_, buffer);
}

void resource_wrapper::read_raw(std::string &buffer) const
{
    auto input = std::vector<std::uint8_t>();
    read_raw(input);

    buffer = std::string(input.begin(), input.end());
}

} // namespace resources
} // namespace aeon
