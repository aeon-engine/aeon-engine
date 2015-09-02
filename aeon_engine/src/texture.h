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

#ifndef texture_h__
#define texture_h__

namespace aeon
{

class texture : public resource
{
public:
    texture(resource_manager *creator, const std::string &name,
            std::uint64_t handle);
    virtual ~texture();

    void bind();

protected:
    virtual bool __load_impl(aeon::streams::stream_ptr stream);
    virtual bool __unload_impl();
    virtual bool __finalize_impl();

    image_ptr image_;
    GLuint texture_;
};

typedef std::shared_ptr<texture> texture_ptr;

} // namespace aeon

#endif // texture_h__
