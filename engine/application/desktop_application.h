/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <build_config.h>
#include <application/base_application.h>
#include <aeon/resources/providers/filesystem_collection_provider.h>
#include <application/gfx_types.h>

namespace aeon
{

/*!
 * Base class for universal desktop games with a single render window.
 */
template <typename scene_manager_t>
class desktop_application : public base_application<selected_gfx_device, selected_platform, scene_manager_t>
{
public:
    /*!
     * Constructor
     * \see base_application::base_application
     */
    explicit desktop_application(const int default_width, const int default_height, const std::string &window_title)
        : base_application<selected_gfx_device, selected_platform, scene_manager_t>(default_width, default_height,
                                                                                    window_title)
    {
    }

    /*!
     * Destructor
     */
    virtual ~desktop_application() = default;
};

} // namespace aeon
