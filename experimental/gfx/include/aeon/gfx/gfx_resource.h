// Copyright (c) 2012-2018 Robin Degen, All Rights Reserved.

#pragma once

namespace aeon::gfx
{

class gfx_resource
{
public:
    gfx_resource(const gfx_resource &) noexcept = delete;
    auto operator=(const gfx_resource &) noexcept -> gfx_resource & = delete;

    gfx_resource(gfx_resource &&) noexcept = delete;
    auto operator=(gfx_resource &&) noexcept -> gfx_resource & = delete;

protected:
    gfx_resource() = default;
    ~gfx_resource() = default;
};

} // namespace aeon::gfx
