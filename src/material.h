#ifndef material_h__
#define material_h__

namespace aeon
{

class material : public resource
{
public:
    material(resource_manager *creator, const std::string &name,
        std::uint64_t handle);
    virtual ~material();

protected:
    virtual bool __load_impl(stream_ptr stream);
    virtual bool __unload_impl();
    virtual bool __finalize_impl();
};

typedef std::shared_ptr<material> material_ptr;

} /* namespace aeon */

#endif /* material_h__ */
