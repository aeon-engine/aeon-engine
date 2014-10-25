#ifndef consolelistener_h__
#define consolelistener_h__

namespace aeon
{

class console_listener
{
public:
    console_listener() {}
    virtual ~console_listener() {}

    virtual void on_log_message(double time_diff, console::log_level level, 
                                const std::string &message) = 0;
};

typedef std::shared_ptr<console_listener> console_listener_ptr;

} /* namespace aeon */

#endif /* consolelistener_h__ */
