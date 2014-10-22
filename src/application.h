#ifndef application_h__
#define application_h__

namespace aeon
{

class application : public framelistener
{
public:
    application();
    ~application();

    void main(int argc, char *argv[]);

    bool on_frame(float dt);
    bool on_render();

private:
    aeon::platforms::glfw *platform_;
};

} /* namespace aeon */

#endif /* application_h__ */
