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

#include <aeon/resources/material.h>

namespace aeon
{
namespace resources
{

material::material(const std::shared_ptr<resource_wrapper> &wrapper, data::material &&material_data)
    : resource(wrapper)
    , logger_(common::logger::get_singleton(), "Resources::Material")
    , material_data_(std::move(material_data))
{
    AEON_LOG_TRACE(logger_) << "Created material resource." << std::endl;
}

material::~material()
{
    AEON_LOG_TRACE(logger_) << "Deleted material resource." << std::endl;
}

} // namespace resources
} // namespace aeon
