#include "Aeon.h"
#include "AeonTexture.h"

namespace Aeon
{

Texture::Texture(ResourceManager *creator, const std::string &name, Handle handle)
:
Resource(creator, name, handle)
{

}

Texture::~Texture()
{

}

} //namespace Aeon
