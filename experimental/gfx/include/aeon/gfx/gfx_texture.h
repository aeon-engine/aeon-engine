// Copyright (c) 2012-2018 Robin Degen, All Rights Reserved.

#pragma once

#include <aeon/gfx/gfx_resource.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size3d.h>
#include <aeon/common/string_table.h>
#include <cstdint>

namespace aeon::gfx
{

struct texture_name_tag
{
};

using texture_name = common::string_table<texture_name_tag>;

class gfx_texture : public gfx_resource
{
public:
    gfx_texture(const gfx_texture &) noexcept = delete;
    auto operator=(const gfx_texture &) noexcept -> gfx_texture & = delete;

    gfx_texture(gfx_texture &&) noexcept = delete;
    auto operator=(gfx_texture &&) noexcept -> gfx_texture & = delete;

protected:
    explicit gfx_texture(const std::uint32_t mips_count, const std::uint32_t samples_count,
                         const imaging::pixel_encoding encoding, const texture_name name);

    ~gfx_texture() = default;

    auto get_mips() const noexcept;
    auto get_samples() const noexcept;
    auto get_encoding() const noexcept;
    auto get_name() const noexcept;

private:
    std::uint32_t mips_count_;
    std::uint32_t samples_count_;
    imaging::pixel_encoding encoding_;
    texture_name name_;
};

inline gfx_texture::gfx_texture(const std::uint32_t mips_count, const std::uint32_t samples_count,
                                const imaging::pixel_encoding encoding, const texture_name name)
    : mips_count_{mips_count}
    , samples_count_{samples_count}
    , encoding_{encoding}
    , name_{name}
{
}

inline auto gfx_texture::get_mips() const noexcept
{
    return mips_count_;
}

inline auto gfx_texture::get_samples() const noexcept
{
    return samples_count_;
}

inline auto gfx_texture::get_encoding() const noexcept
{
    return encoding_;
}

inline auto gfx_texture::get_name() const noexcept
{
    return name_;
}

class gfx_texture2d : public gfx_texture
{
public:
    gfx_texture2d(const gfx_texture2d &) noexcept = delete;
    auto operator=(const gfx_texture2d &) noexcept -> gfx_texture2d & = delete;

    gfx_texture2d(gfx_texture2d &&) noexcept = delete;
    auto operator=(gfx_texture2d &&) noexcept -> gfx_texture2d & = delete;

    auto get_size() const noexcept;

protected:
    explicit gfx_texture2d(const math::size2d<imaging::dimension> size, const std::uint32_t mips_count,
                           const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                           const texture_name name);

    ~gfx_texture2d() = default;

private:
    math::size2d<imaging::dimension> size_;
};

inline gfx_texture2d::gfx_texture2d(const math::size2d<imaging::dimension> size, const std::uint32_t mips_count,
                                    const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                                    const texture_name name)
    : gfx_texture{mips_count, samples_count, encoding, name}
    , size_{size}
{
}

inline auto gfx_texture2d::get_size() const noexcept
{
    return size_;
}

class gfx_texture3d : public gfx_texture
{
public:
    gfx_texture3d(const gfx_texture3d &) noexcept = delete;
    auto operator=(const gfx_texture3d &) noexcept -> gfx_texture3d & = delete;

    gfx_texture3d(gfx_texture3d &&) noexcept = delete;
    auto operator=(gfx_texture3d &&) noexcept -> gfx_texture3d & = delete;

    auto get_size() const noexcept;

protected:
    explicit gfx_texture3d(const math::size3d<imaging::dimension> size, const std::uint32_t mips_count,
                           const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                           const texture_name name);

    ~gfx_texture3d() = default;

private:
    math::size3d<imaging::dimension> size_;
};

inline gfx_texture3d::gfx_texture3d(const math::size3d<imaging::dimension> size, const std::uint32_t mips_count,
                                    const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                                    const texture_name name)
    : gfx_texture{mips_count, samples_count, encoding, name}
    , size_{size}
{
}

inline auto gfx_texture3d::get_size() const noexcept
{
    return size_;
}

class gfx_texture_cube : public gfx_texture
{
public:
    gfx_texture_cube(const gfx_texture_cube &) noexcept = delete;
    auto operator=(const gfx_texture_cube &) noexcept -> gfx_texture_cube & = delete;

    gfx_texture_cube(gfx_texture_cube &&) noexcept = delete;
    auto operator=(gfx_texture_cube &&) noexcept -> gfx_texture_cube & = delete;

    auto get_size() const noexcept;

protected:
    explicit gfx_texture_cube(const imaging::dimension size, const std::uint32_t mips_count,
                              const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                              const texture_name name);

    ~gfx_texture_cube() = default;

private:
    imaging::dimension size_;
};

inline gfx_texture_cube::gfx_texture_cube(const imaging::dimension size, const std::uint32_t mips_count,
                                          const std::uint32_t samples_count, const imaging::pixel_encoding encoding,
                                          const texture_name name)
    : gfx_texture{mips_count, samples_count, encoding, name}
    , size_{size}
{
}

inline auto gfx_texture_cube::get_size() const noexcept
{
    return size_;
}

} // namespace aeon::gfx
