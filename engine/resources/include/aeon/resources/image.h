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

#include <aeon/resources/resource.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/common/logger.h>
#include <aeon/data/image.h>
#include <memory>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(image_exception, resource_exception, "Image resource exception.");
DEFINE_EXCEPTION_OBJECT(image_data_exception, image_exception, "Image resource data exception.");

class image : public resource
{
public:
    explicit image(data::image &&image_data);

    virtual ~image();

    const auto &get_data() const
    {
        return image_data_;
    }

private:
    logger::logger logger_;
    data::image image_data_;
};

} // namespace resources
} // namespace aeon
