#ifndef AeonTextureManager_h__
#define AeonTextureManager_h__

#include "Aeon/Resources/ResourceManager.h"
#include "Aeon/Utility/Singleton.h"
#include "Aeon/Streams/Stream.h"
#include "Aeon/Resources/Texture.h"

namespace Aeon
{

class TextureManager : public ResourceManager, public Singleton<TextureManager>
{
public:
	TextureManager();
	virtual ~TextureManager();

	TexturePtr		load(StreamPtr stream);
	TexturePtr		load(const std::string &name);

protected:
	Resource *		__create_new_resource(const std::string &name);
};

} /* namespace Aeon */

#endif /* AeonTextureManager_h__ */
