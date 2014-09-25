#include "aeon/stdafx.h"

namespace aeon
{

texture::texture(resource_manager *creator, const std::string &name, 
    std::uint64_t handle)
:
resource(creator, name, handle),
texture_(0)
{

}

texture::~texture()
{

}

void texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture_);
}

bool texture::__load_impl(stream_ptr stream)
{
    image_ = image_codec_manager::get_singleton().decode("PNG", stream);

    if (!image_)
    {
        console::warning("[Texture]: Texture '%s' could not be loaded. "
            "Image decode reported an error.", stream->get_name().c_str());
        return false;
    }

    return true;
}

bool texture::__unload_impl()
{
    if (texture_ == 0)
    {
        console::warning("[Texture]: Texture '%s' could not be unloaded. "
            "Unload called on previously unloaded texture.");
        return false;
    }

    console::debug("[Texture]: Deleting OpenGL texture handle %u.", texture_);

    glDeleteTextures(1, &texture_);
    texture_ = 0;

    return true;
}

bool texture::__finalize_impl()
{
    if (!image_ || !image_->get_data())
    {
        console::warning("[Texture]: Texture could not be finalized. "
            "Image is invalid.");
        return false;
    }

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    console::debug("[Texture]: Finalizing OpenGL texture handle %u.", 
        texture_);

    GLenum glpixelformat = 0;

    switch (image_->get_pixelformat())
    {
        case image::pixel_format::rgb:
        {
            glpixelformat = GL_RGB;
            console::debug("[Texture]: Image pixelformat is RGB.");
        }break;
        case image::pixel_format::rgba:
        {
            glpixelformat = GL_RGBA;
            console::debug("[Texture]: Image pixelformat is RGBA.");
        }break;
        default:
        {
            console::error("[Texture]: Failed to load texture: Unknown "
                "pixel format given.");
            return false;
        }
    }

    GLsizei width = (GLsizei)image_->get_width();
    GLsizei height = (GLsizei)image_->get_height();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, glpixelformat, width, height, 0, 
        glpixelformat, GL_UNSIGNED_BYTE, image_->get_data()->get());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Remove our reference to this image so it can be unloaded when no 
    // longer in use.
    image_.reset();

    return true;
}

} /* namespace aeon */
