/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#ifndef modelcodecassimp_h__
#define modelcodecassimp_h__

namespace aeon
{

class scene_codec_assimp : public scene_codec
{
public:
    scene_codec_assimp();
    virtual ~scene_codec_assimp();

    virtual scene_ptr decode(aeon::streams::stream_ptr stream);
    virtual std::string get_type_name() const;
};

} // namespace aeon

#endif // modelcodecassimp_h__
