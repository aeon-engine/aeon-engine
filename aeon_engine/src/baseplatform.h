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

#ifndef baseplatform_h__
#define baseplatform_h__

namespace aeon
{

class root;

namespace platforms
{

class base_platform
{
friend class aeon::root;
public:
    base_platform() {}
    virtual ~base_platform() {}

protected:
    virtual bool initialize() = 0;

    virtual bool pre_frame() = 0;
    virtual bool post_frame() = 0;

    virtual bool dispose() = 0;
};

typedef std::shared_ptr<base_platform> base_platform_ptr;

} // namespace platforms
} // namespace aeon

#endif // baseplatform_h__
