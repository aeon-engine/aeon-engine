#ifndef root_h__
#define root_h__

namespace aeon
{

typedef std::list<framelistener *> framelisteners;

class root : public singleton<root>
{
public:
    ~root();

    static bool initialize(platforms::base_platform_ptr platform);

    void run();
    void stop();

    void add_frame_listener(framelistener *listener);
    void remove_frame_listener(framelistener *listener);
    void remove_all_frame_listeners();

protected:
    root(platforms::base_platform_ptr platform);

    bool __initialize_impl(platforms::base_platform_ptr platform);

    bool initialized_;
    bool running_;

    framelisteners frame_listeners_;
    platforms::base_platform_ptr platform_;
};

} /* namespace aeon */

#endif /* root_h__ */
