#include "Aeon.h"
#include "AeonImageCodecManager.h"
#include "AeonConsole.h"

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
	m_registered_codecs[name] = codec;
}

ImagePtr ImageCodecManager::decode(const std::string &name, StreamPtr stream)
{
	auto codec = m_registered_codecs.find(name);

	//Could not find the codec?
	if(codec == m_registered_codecs.end())
	{
		Console::error("ImageCodecManager: Could not decode stream. Unknown decoder: '%s'", name.c_str());
		return AeonEmptyImage;
	}

	return codec->second->decode(stream);
}

} //namespace Aeon
