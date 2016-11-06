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
    explicit image(const std::shared_ptr<resource_wrapper> &wrapper, data::image &&image_data);

    virtual ~image();

    const auto &get_data() const
    {
        return image_data_;
    }

    auto get_image_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<image_resource_wrapper>(get_resource_wrapper());
    }

private:
    logger::logger logger_;
    data::image image_data_;
};

} // namespace resources
} // namespace aeon
