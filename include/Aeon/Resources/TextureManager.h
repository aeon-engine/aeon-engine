#ifndef AeonTextureManager_h__
#define AeonTextureManager_h__

#include "AeonResourceManager.h"
#include "AeonSingleton.h"

namespace Aeon
{

class TextureManager : public ResourceManager, public Singleton<TextureManager>
{
public:
	TextureManager();
	virtual ~TextureManager();

	//TexturePtr loadImage(

protected:
	Resource * __create_internal(const std::string &name, Resource::Handle handle);
};

} //namespace Aeon

#endif // AeonTextureManager_h__
