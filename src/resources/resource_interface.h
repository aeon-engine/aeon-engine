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

#include <resources/resource_type.h>
#include <memory>
#include <common/buffer.h>

namespace aeon
{
namespace resources
{

class resource;

class resource_interface;
using resource_interface_ptr = std::shared_ptr<resource_interface>;

class resource_interface
{
friend class resource;
public:
    virtual ~resource_interface();

private:
    resource_interface(resource &parent, common::buffer_u8 &&buffer);

    resource &parent_;
    common::buffer_u8 buffer_;
};



} // namespace resources
} // namespace aeon
