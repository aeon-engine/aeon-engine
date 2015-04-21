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

#ifndef texturemanager_h__
#define texturemanager_h__

namespace aeon
{

class texture_manager : public resource_manager,
                        public aeon::utility::singleton<texture_manager>
{
public:
    texture_manager();
    virtual ~texture_manager();

    texture_ptr load(aeon::streams::stream_ptr stream);
    texture_ptr load(const std::string &name);

protected:
    resource *__create_new_resource(const std::string &name);
};

} // namespace aeon

#endif // texturemanager_h__
