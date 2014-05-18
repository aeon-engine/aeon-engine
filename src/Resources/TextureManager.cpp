#include "Aeon/Aeon.h"
#include "Aeon/Resources/TextureManager.h"
#include "Aeon/Resources/Texture.h"
#include "Aeon/Console/Console.h"

AeonInitializeSingleton(Aeon::TextureManager);

namespace Aeon
{

TextureManager::TextureManager()
{
	Console::debug("[TextureManager]: created.");
}

TextureManager::~TextureManager()
{
	Console::debug("[TextureManager]: disposed.");
}

TexturePtr TextureManager::load(StreamPtr stream)
{
	return std::dynamic_pointer_cast<Texture>(ResourceManager::load(stream));
}

TexturePtr TextureManager::load(const std::string &name)
{
	return std::dynamic_pointer_cast<Texture>(ResourceManager::load(name));
}

void TextureManager::finalize_textures()
{

}

Resource * TextureManager::__create_new_resource(const std::string &name)
{
	return new Texture(this, name);
}

} /* namespace Aeon */
