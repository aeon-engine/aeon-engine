#ifndef materialmanager_h__
#define materialmanager_h__

namespace aeon
{

class material_manager : public resource_manager,
                         public singleton<material_manager>
{
public:
    material_manager();
    virtual ~material_manager();

    material_ptr load(stream_ptr stream);
    material_ptr load(const std::string &name);

protected:
    resource *__create_new_resource(const std::string &name);
};

} /* namespace aeon */

#endif /* materialmanager_h__ */
