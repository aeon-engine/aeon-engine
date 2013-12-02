#include "Aeon.h"
#include "AeonTextureManager.h"
#include "AeonTexture.h"

AeonInitializeSingleton(Aeon::TextureManager);

namespace Aeon
{

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

Resource * TextureManager::__create_internal(const std::string &name, Resource::Handle handle)
{
	return new Texture(this, name, handle);
}

} //namespace Aeon
