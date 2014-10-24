#ifndef modelcodecassimp_h__
#define modelcodecassimp_h__

namespace aeon
{

class scene_codec_assimp : public scene_codec
{
public:
    scene_codec_assimp();
    virtual ~scene_codec_assimp();

    virtual scene_ptr decode(stream_ptr stream);
    virtual std::string get_type_name() const;
};

} /* namespace aeon */

#endif /* modelcodecassimp_h__ */
