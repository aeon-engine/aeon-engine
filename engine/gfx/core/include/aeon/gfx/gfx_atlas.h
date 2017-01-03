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

#include <aeon/common/cached_object.h>
#include <aeon/common/exception.h>
#include <aeon/common/logger.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/data/atlas.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace gfx
{

DEFINE_EXCEPTION_OBJECT(atlas_exception, aeon::common::exception, "Generic Atlas exception.");

class atlas : public common::cached_object, public std::enable_shared_from_this<atlas>
{
    friend class gfx_atlas_manager;

public:
    explicit atlas(const std::shared_ptr<material> &material, const data::atlas &atlas);
    explicit atlas(const std::shared_ptr<material> &material, glm::vec2 sprite_size);
    virtual ~atlas() = default;

    data::atlas::region get_region_by_index(int index);
    data::atlas::region get_region_by_name(const std::string &name);

    std::shared_ptr<material> get_material() const;

private:
    void __calculate_atlas_regions(glm::vec2 sprite_size);

    aeon::logger::logger logger_;

    std::shared_ptr<material> material_;
    data::atlas atlas_;
};

} // namespace gfx
} // namespace aeon
