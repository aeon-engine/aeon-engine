#ifndef streamlistener_h__
#define streamlistener_h__

namespace aeon
{

class console_stream_listener : public console_listener
{
public:
    console_stream_listener(stream_ptr stream);
    ~console_stream_listener();

    void on_log_message(double time_diff, console::log_level level, 
        const std::string &message);

private:
    stream_ptr stream_;
};

} /* namespace aeon */

#endif /* streamlistener_h__ */
