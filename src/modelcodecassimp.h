#ifndef modelcodecassimp_h__
#define modelcodecassimp_h__

namespace aeon
{

class model_codec_assimp : public model_codec
{
public:
    model_codec_assimp();
    virtual ~model_codec_assimp();

    virtual model_ptr decode(stream_ptr stream);
    virtual std::string get_type_name() const;
};

} /* namespace aeon */

#endif /* modelcodecassimp_h__ */
