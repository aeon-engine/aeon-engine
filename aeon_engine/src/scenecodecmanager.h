/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#ifndef modelcodecmanager_h__
#define modelcodecmanager_h__

namespace aeon
{

class scene_codec_manager : public aeon::utility::singleton<scene_codec_manager>
{
public:
    scene_codec_manager();
    virtual ~scene_codec_manager();

    void register_codec(scene_codec_ptr codec);

    scene_ptr decode(const std::string &name, aeon::streams::stream_ptr stream);

private:
    typedef std::map<const std::string, scene_codec_ptr> scene_codecs;
    scene_codecs registered_codecs_;
};

} // namespace aeon

#endif // modelcodecmanager_h__
