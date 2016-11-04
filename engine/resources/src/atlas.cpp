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

#include <aeon/resources/atlas.h>
#include <cassert>

namespace aeon
{
namespace resources
{

atlas::atlas(const std::shared_ptr<resource_wrapper> &wrapper, const std::string &material_path,
             const data::atlas &data)
    : resource(wrapper)
    , logger_(common::logger::get_singleton(), "Resources::Atlas")
    , data_(data)
    , material_path_(material_path)
{
    AEON_LOG_TRACE(logger_) << "Created atlas resource based on regions." << std::endl;
}

atlas::~atlas()
{
    AEON_LOG_TRACE(logger_) << "Deleted atlas resource." << std::endl;
}

const std::string &atlas::get_material_path() const
{
    return material_path_;
}

const data::atlas &atlas::get_data() const
{
    return data_;
}

} // namespace resources
} // namespace aeon
