#ifndef AeonTexture_h__
#define AeonTexture_h__

#include "AeonResource.h"

namespace Aeon
{

class Texture : public Resource
{
public:
	Texture(ResourceManager *creator, const std::string &name, Handle handle);
	virtual ~Texture();

};

} //namespace Aeon

#endif // AeonTexture_h__
