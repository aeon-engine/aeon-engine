/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/codecs/codec.h>
#include <aeon/resources/mesh.h>

namespace aeon
{
namespace resources
{

class mesh;
class mesh_resource_wrapper;
class resource_manager;

class mesh_codec : public codec
{
public:
    mesh_codec() = default;
    virtual ~mesh_codec() = default;

    virtual auto decode(resource_manager &parent, const std::shared_ptr<mesh_resource_wrapper> &wrapper) const
        -> std::shared_ptr<mesh> = 0;
};

} // namespace resources
} // namespace aeon
