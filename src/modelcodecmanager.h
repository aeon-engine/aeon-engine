#ifndef modelcodecmanager_h__
#define modelcodecmanager_h__

namespace aeon
{

class model_codec_manager : public singleton<model_codec_manager>
{
public:
    model_codec_manager();
    ~model_codec_manager();

    void register_codec(model_codec_ptr codec);

    model_ptr decode(const std::string &name, stream_ptr stream);

private:
    typedef std::map<const std::string, model_codec_ptr> model_codecs;
    model_codecs registered_codecs_;
};

} /* namespace aeon */

#endif /* modelcodecmanager_h__ */
