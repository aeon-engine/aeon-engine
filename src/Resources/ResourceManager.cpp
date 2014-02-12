#include "Aeon.h"
#include "AeonResourceManager.h"
#include "AeonConsole.h"

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
