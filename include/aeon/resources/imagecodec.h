#ifndef imagecodec_h__
#define imagecodec_h__

#include "aeon/streams/stream.h"
#include "aeon/resources/image.h"

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

} /* namespace aeon */

#endif /* imagecodec_h__ */
