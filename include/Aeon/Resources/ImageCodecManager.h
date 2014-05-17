#ifndef AeonImageCodecManager_h__
#define AeonImageCodecManager_h__

#include "Aeon/Utility/Singleton.h"
#include "Aeon/Resources/ImageCodec.h"
#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class ImageCodecManager : public Singleton<ImageCodecManager>
{
public:
	ImageCodecManager();
	~ImageCodecManager();

	void				register_codec(ImageCodecPtr codec);
	
	ImagePtr			decode(const std::string &name, StreamPtr stream);

private:
	typedef std::map<const std::string, ImageCodecPtr> ImageCodecs;
	ImageCodecs			registered_codecs_;
};

} //namespace Aeon

#endif /* AeonImageCodecManager_h__ */
