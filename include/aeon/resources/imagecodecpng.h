#ifndef imagecodecpng_h__
#define imagecodecpng_h__

#include "aeon/resources/imagecodec.h"

namespace aeon
{

class image_codec_png : public image_codec
{
public:
    image_codec_png();
    virtual ~image_codec_png();

    virtual image_ptr decode(stream_ptr stream);
    virtual std::string get_type_name() const;    
};

} //namespace aeon

#endif // imagecodecpng_h__
