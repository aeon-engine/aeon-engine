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
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/data/atlas.h>
#include <aeon/common/buffer.h>
#include <aeon/common/logger.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace aeon
{
namespace resources
{

class atlas : public resource
{
public:
    /*!
     * Constructor used by the atlas codec to load an atlas
     */
    explicit atlas(resource_wrapper_ptr wrapper, const std::string &material_path, const data::atlas &data);

    virtual ~atlas();

    const std::string &get_material_path() const;
    const data::atlas &get_data() const;

    atlas_resource_wrapper_ptr get_atlas_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<atlas_resource_wrapper>(get_resource_wrapper());
    }

private:
    aeon::logger::logger logger_;

    data::atlas data_;
    std::string material_path_;
};

using atlas_ptr = std::shared_ptr<atlas>;

} // namespace resources
} // namespace aeon
