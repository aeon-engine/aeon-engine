#include "Aeon/Aeon.h"
#include "Aeon/Resources/ImageCodecManager.h"
#include "Aeon/Console/Console.h"

AeonInitializeSingleton(Aeon::ImageCodecManager);

namespace Aeon
{

ImageCodecManager::ImageCodecManager()
{

}

ImageCodecManager::~ImageCodecManager()
{

}

void ImageCodecManager::register_codec(ImageCodecPtr codec)
{
	if(!codec)
		return;
	
	const std::string &name = codec->get_type_name();
	registered_codecs_[name] = codec;
}

ImagePtr ImageCodecManager::decode(const std::string &name, StreamPtr stream)
{
	auto codec = registered_codecs_.find(name);

	//Could not find the codec?
	if(codec == registered_codecs_.end())
	{
		Console::error("ImageCodecManager: Could not decode stream. Unknown decoder: '%s'", name.c_str());
		return AeonEmptyImage;
	}

	return codec->second->decode(stream);
}

} //namespace Aeon
