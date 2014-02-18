#ifndef AeonTextureManager_h__
#define AeonTextureManager_h__

#include "Aeon/Resources/ResourceManager.h"
#include "Aeon/Utility/Singleton.h"

namespace Aeon
{

class TextureManager : public ResourceManager, public Singleton<TextureManager>
{
public:
	TextureManager();
	virtual ~TextureManager();

	//TexturePtr loadImage(
	
	//Call this only from the OpenGL render thread.
	void finalize_textures();

protected:
	Resource * __create_internal(const std::string &name, Resource::Handle handle);
};

} //namespace Aeon

#endif // AeonTextureManager_h__
