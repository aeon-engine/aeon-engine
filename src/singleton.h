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

#ifndef singleton_h__
#define singleton_h__

#define aeon_initialize_singleton(type) \
    template <> type * aeon::singleton <type>::instance_ = NULL

namespace aeon
{

template <class type>
class singleton
{
public:
    singleton()
    {
        assert(instance_ == NULL);
        instance_ = static_cast<type *>(this);

        if (instance_ == NULL)
        {
            throw std::exception();
        }
    }

    virtual ~singleton()
    {
        instance_ = NULL;
    }

    static type *create()
    {
        return new type;
    }

    static void dispose()
    {
        if (instance_ != NULL)
            delete (type *)instance_;
    }

    static type & get_singleton()
    {
        assert(instance_);

        if (instance_ == NULL)
        {
            throw std::exception();
        }

        return *instance_;
    }

    static type * get_singleton_ptr()
    {
        return instance_;
    }

protected:
    static type * instance_;

};

} /* namespace aeon */

#endif /* singleton_h__ */
