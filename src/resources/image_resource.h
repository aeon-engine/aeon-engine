/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <resources/resource.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

class image;
using image_ptr = std::shared_ptr<image>;

class image_resource : public resource
{
friend class resource_interface;
friend class resource_manager;
public:
    virtual ~image_resource();

    image_ptr open();

protected:
    image_resource(resource_manager &parent, const std::string &path,
        resource_provider_weak_ptr provider);

};

using image_resource_ptr = std::shared_ptr<image_resource>;

} // namespace resources
} // namespace aeon
