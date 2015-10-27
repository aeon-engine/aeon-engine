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

#include <common/types/rectangle.h>
#include <memory>

namespace aeon
{
namespace scene
{

class viewport
{
public:
    viewport(const common::types::rectangle<float> &rect, int zorder);
    virtual ~viewport();

    void set_rectangle(const common::types::rectangle<float> &rect)
    {
        rectangle_ = rect;
    }

private:
    common::types::rectangle<float> rectangle_;
    int zorder_;
};

using viewport_ptr = std::shared_ptr<viewport>;

} // namespace scene
} // namespace aeon
