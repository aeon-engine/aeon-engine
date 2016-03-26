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

#include <resources/wrappers/resource_wrapper.h>
#include <memory>
#include <string>

namespace aeon
{
namespace audio
{
    class buffer;
    using buffer_ptr = std::shared_ptr<buffer>;
    using sound_ptr = buffer_ptr;
    using stream_ptr = buffer_ptr;
} // namespace audio

namespace resources
{
class sound_resource_wrapper : public resource_wrapper
{
public:
    explicit sound_resource_wrapper(resource_manager &parent, const std::string &path,
                                    resource_provider_weak_ptr provider);
    virtual ~sound_resource_wrapper() = default;

    audio::sound_ptr open();
};

using sound_resource_wrapper_ptr = std::shared_ptr<sound_resource_wrapper>;


class stream_resource_wrapper : public resource_wrapper
{
public:
    explicit stream_resource_wrapper(resource_manager &parent, const std::string &path,
        resource_provider_weak_ptr provider);
    virtual ~stream_resource_wrapper() = default;

    audio::stream_ptr open();
};

using stream_resource_wrapper_ptr = std::shared_ptr<stream_resource_wrapper>;


} // namespace resources
} // namespace aeon
