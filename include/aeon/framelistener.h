#ifndef framelistener_h__
#define framelistener_h__

namespace aeon
{

class framelistener
{
public:
    framelistener() {}
    ~framelistener() {}

    virtual bool on_frame(float dt) = 0;
    virtual bool on_render() = 0;
};

} //namespace Aeon

#endif // framelistener_h__
