#ifndef AeonImageCodec_h__
#define AeonImageCodec_h__

#include "Aeon/Streams/Stream.h"
#include "Aeon/Resources/Image.h"

namespace aeon
{

class image_codec
{
public:
    image_codec() {}
    virtual ~image_codec() {}

    virtual image_ptr decode(stream_ptr stream) = 0;
    virtual std::string get_type_name() const = 0;

};

typedef std::shared_ptr<image_codec> image_codec_ptr;

} /* namespace Aeon */

#endif /* AeonImageCodec_h__ */
