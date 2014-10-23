#ifndef modelcodec_h__
#define modelcodec_h__

namespace aeon
{

class model_codec
{
public:
    model_codec() {}
    virtual ~model_codec() {}

    virtual model_ptr decode(stream_ptr stream) = 0;
    virtual std::string get_type_name() const = 0;

};

typedef std::shared_ptr<model_codec> model_codec_ptr;

} /* namespace aeon */

#endif /* modelcodec_h__ */
