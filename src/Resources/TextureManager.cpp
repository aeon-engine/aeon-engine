#include "Aeon/Aeon.h"
#include "Aeon/Resources/TextureManager.h"
#include "Aeon/Resources/Texture.h"
#include "Aeon/Console/Console.h"

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

void TextureManager::finalize_textures()
{

}

Resource * TextureManager::__create_internal(const std::string &name, Resource::Handle handle)
{
	return new Texture(this, name, handle);
}

} /* namespace Aeon */
