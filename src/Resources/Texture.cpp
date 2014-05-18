#include "Aeon/Aeon.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Resources/Texture.h"
#include "Aeon/Resources/Image.h"
#include "Aeon/Resources/ImageCodecManager.h"

namespace Aeon
{

Texture::Texture(ResourceManager *creator, const std::string &name)
:
Resource(creator, name),
texture_(0)
{

}

Texture::~Texture()
{

}

void Texture::unload()
{
	glDeleteTextures(1, &texture_);
}

bool Texture::__load(StreamPtr stream)
{
	image_ = ImageCodecManager::getSingleton().decode("PNG", stream);

	if (!image_)
	{
		Console::warning("[Texture]: Texture '%s' could not be loaded. Image decode reported an error.", stream->get_name().c_str());
		return false;
	}

	return true;
}

bool Texture::__finalize()
{
	if (!image_ || !image_->get_data())
	{
		Console::warning("[Texture]: Texture could not be finalized. Image is invalid.");
		return false;
	}


	return true;
}

} /* namespace Aeon */
