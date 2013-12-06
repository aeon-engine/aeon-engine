#include "Aeon.h"
#include "AeonTextureManager.h"
#include "AeonTexture.h"
#include "AeonConsole.h"

AeonInitializeSingleton(Aeon::TextureManager);

namespace Aeon
{

TextureManager::TextureManager()
{
	Console::debug("TextureManager created.");
}

TextureManager::~TextureManager()
{
	Console::debug("TextureManager disposed.");
}

Resource * TextureManager::__create_internal(const std::string &name, Resource::Handle handle)
{
	return new Texture(this, name, handle);
}

} //namespace Aeon
