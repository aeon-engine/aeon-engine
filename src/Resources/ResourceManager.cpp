#include "Aeon/Aeon.h"
#include "Aeon/Resources/ResourceManager.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

ResourceManager::ResourceManager()
{
	Console::debug("ResourceManager created.");
}

ResourceManager::~ResourceManager()
{
	Console::debug("ResourceManager disposed.");
}

} //namespace Aeon
