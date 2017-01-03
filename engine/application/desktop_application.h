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

#include <build_config.h>
#include <application/base_application.h>
#include <aeon/resources/providers/filesystem_provider.h>
#include <application/gfx_types.h>

namespace aeon
{

/*!
 * Base class for universal desktop games with a single render window.
 */
template <typename scene_manager_t>
class desktop_application : public base_application<selected_gfx_device, scene_manager_t>
{
public:
    /*!
     * Constructor
     * \see base_application::base_application
     */
    explicit desktop_application(const int default_width, const int default_height, const std::string &window_title)
        : base_application<selected_gfx_device, scene_manager_t>(default_width, default_height, window_title)
    {
    }

    /*!
     * Destructor
     */
    virtual ~desktop_application() = default;
};

} // namespace aeon
