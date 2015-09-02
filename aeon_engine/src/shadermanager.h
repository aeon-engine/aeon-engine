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

#ifndef shadermanager_h__
#define shadermanager_h__

namespace aeon
{

class shader_manager : public resource_manager,
                       public aeon::utility::singleton<shader_manager>
{
public:
    shader_manager();
    virtual ~shader_manager();

    shader_ptr load(aeon::streams::stream_ptr stream);
    shader_ptr load(const std::string &name);

protected:
    resource *__create_new_resource(const std::string &name);
};

} // namespace aeon

#endif // shadermanager_h__
