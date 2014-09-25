#ifndef imagecodecmanager_h__
#define imagecodecmanager_h__

#include "aeon/utility/singleton.h"
#include "aeon/resources/imagecodec.h"
#include "aeon/streams/stream.h"

namespace aeon
{

class image_codec_manager : public singleton<image_codec_manager>
{
public:
    image_codec_manager();
    ~image_codec_manager();

    void register_codec(image_codec_ptr codec);
    
    image_ptr decode(const std::string &name, stream_ptr stream);

private:
    typedef std::map<const std::string, image_codec_ptr> image_codecs;
    image_codecs registered_codecs_;
};

} //namespace aeon

#endif // imagecodecmanager_h__
