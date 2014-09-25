#ifndef texturemanager_h__
#define texturemanager_h__

#include "aeon/resources/resourcemanager.h"
#include "aeon/utility/singleton.h"
#include "aeon/streams/stream.h"
#include "aeon/resources/texture.h"

namespace aeon
{

class texture_manager : public resource_manager, 
    public singleton<texture_manager>
{
public:
    texture_manager();
    virtual ~texture_manager();

    texture_ptr load(stream_ptr stream);
    texture_ptr load(const std::string &name);

protected:
    resource *__create_new_resource(const std::string &name);
};

} //namespace aeon

#endif // texturemanager_h__
