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

#include <string>
#include <build_config.h>

namespace aeon
{

class application_settings
{
public:
    application_settings()
        : window_size_hint_width(AEON_DEFAULT_WINDOW_WIDTH_HINT)
        , window_size_hint_height(AEON_DEFAULT_WINDOW_HEIGHT_HINT)
        , window_title_hint(AEON_DEFAULT_WINDOW_TITLE_HINT)
    {
    }

    virtual ~application_settings() = default;

    int window_size_hint_width;
    int window_size_hint_height;
    std::string window_title_hint;
};

} // namespace aeon
