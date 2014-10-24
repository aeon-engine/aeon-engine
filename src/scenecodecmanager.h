#ifndef modelcodecmanager_h__
#define modelcodecmanager_h__

namespace aeon
{

class scene_codec_manager : public singleton<scene_codec_manager>
{
public:
    scene_codec_manager();
    ~scene_codec_manager();

    void register_codec(scene_codec_ptr codec);

    scene_ptr decode(const std::string &name, stream_ptr stream);

private:
    typedef std::map<const std::string, scene_codec_ptr> scene_codecs;
    scene_codecs registered_codecs_;
};

} /* namespace aeon */

#endif /* modelcodecmanager_h__ */
