#ifndef modelcodec_h__
#define modelcodec_h__

namespace aeon
{

class scene_codec
{
public:
    scene_codec() {}
    virtual ~scene_codec() {}

    virtual scene_ptr decode(stream_ptr stream) = 0;
    virtual std::string get_type_name() const = 0;

};

typedef std::shared_ptr<scene_codec> scene_codec_ptr;

} /* namespace aeon */

#endif /* modelcodec_h__ */
