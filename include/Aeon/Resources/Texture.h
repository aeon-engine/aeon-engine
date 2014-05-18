#ifndef AeonTexture_h__
#define AeonTexture_h__

#include "Aeon/Resources/Resource.h"
#include "Aeon/Streams/Stream.h"
#include "Aeon/Resources/Image.h"

namespace Aeon
{

class Texture : public Resource
{
public:
	Texture(ResourceManager *creator, const std::string &name);
	virtual ~Texture();

	void					unload();

protected:
	virtual bool			__load(StreamPtr stream);
	virtual bool			__finalize();

	ImagePtr				image_;
	GLuint					texture_;
};

typedef std::shared_ptr<Texture> TexturePtr;
#define AeonEmptyTexture TexturePtr()

} /* namespace Aeon */

#endif /* AeonTexture_h__ */
