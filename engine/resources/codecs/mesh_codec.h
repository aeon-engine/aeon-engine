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

#include <resources/exceptions.h>
#include <aeon/common/buffer.h>
#include <resources/resource_encoding.h>
#include <resources/codecs/codec.h>
#include <resources/mesh.h>

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

    virtual mesh_ptr decode(resource_manager &parent, mesh_resource_wrapper_ptr wrapper) = 0;
};

using mesh_codec_ptr = std::unique_ptr<mesh_codec>;

} // namespace resources
} // namespace aeon
