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

#ifndef imagecodecmanager_h__
#define imagecodecmanager_h__

namespace aeon
{

class image_codec_manager : public aeon::utility::singleton<image_codec_manager>
{
public:
    image_codec_manager();
    virtual ~image_codec_manager();

    void register_codec(image_codec_ptr codec);

    image_ptr decode(const std::string &name, aeon::streams::stream_ptr stream);

private:
    typedef std::map<const std::string, image_codec_ptr> image_codecs;
    image_codecs registered_codecs_;
};

} // namespace aeon

#endif // imagecodecmanager_h__
