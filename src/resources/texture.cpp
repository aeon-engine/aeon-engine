#include "aeon/aeon.h"
#include "aeon/console/console.h"
#include "aeon/resources/texture.h"
#include "aeon/resources/image.h"
#include "aeon/resources/imagecodecmanager.h"

namespace aeon
{

texture::texture(resource_manager *creator, const std::string &name)
:
resource(creator, name),
texture_(0)
{

}

texture::~texture()
{

}

bool texture::__load_impl(stream_ptr stream)
{
	image_ = image_codec_manager::get_singleton().decode("PNG", stream);

	if (!image_)
	{
		console::warning("[Texture]: Texture '%s' could not be loaded. Image decode reported an error.", stream->get_name().c_str());
		return false;
	}

	return true;
}

bool texture::__unload_impl()
{
	if (texture_ == 0)
	{
		console::warning("[Texture]: Texture '%s' could not be unloaded. Unload called on previously unloaded texture.");
		return false;
	}

	glDeleteTextures(1, &texture_);
	texture_ = 0;

	return true;
}

bool texture::__finalize_impl()
{
	if (!image_ || !image_->get_data())
	{
		console::warning("[Texture]: Texture could not be finalized. Image is invalid.");
		return false;
	}

	return true;
}

} //namespace aeon
