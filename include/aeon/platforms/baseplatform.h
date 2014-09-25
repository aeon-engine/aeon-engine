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

} /* namespace platforms */
} /* namespace aeon */

#endif /* baseplatform_h__ */
