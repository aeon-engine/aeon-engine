#ifndef AeonImageCodecManager_h__
#define AeonImageCodecManager_h__

#include "AeonSingleton.h"

namespace Aeon
{

class ImageCodecManager : Singleton<ImageCodecManager>
{
public:
	ImageCodecManager();
	~ImageCodecManager();
};

} //namespace Aeon

#endif // AeonImageCodecManager_h__
