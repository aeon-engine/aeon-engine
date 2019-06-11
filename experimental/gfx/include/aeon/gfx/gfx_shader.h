// Copyright (c) 2012-2018 Robin Degen, All Rights Reserved.

#pragma once

#include <aeon/gfx/gfx_resource.h>
#include <aeon/common/string_table.h>

namespace aeon::gfx
{

struct shader_name_tag
{
};

using shader_name = common::string_table<shader_name_tag>;

class gfx_shader : public gfx_resource
{
public:
    gfx_shader(const gfx_shader &) noexcept = delete;
    auto operator=(const gfx_shader &) noexcept -> gfx_shader & = delete;

    gfx_shader(gfx_shader &&) noexcept = delete;
    auto operator=(gfx_shader &&) noexcept -> gfx_shader & = delete;

protected:
    explicit gfx_shader(const shader_name name);

    ~gfx_shader() = default;

    auto get_name() const noexcept;

private:
    shader_name name_;
};

inline gfx_shader::gfx_shader(const shader_name name)
    : name_{name}
{
}

inline auto gfx_shader::get_name() const noexcept
{
    return name_;
}

} // namespace aeon::gfx
