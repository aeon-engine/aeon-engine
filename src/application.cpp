#include "stdafx.h"

#include "application.h"
#include "rpggame.h"

namespace aeon
{

application::application() :
    platform_(NULL)
{

}

application::~application()
{
    if (platform_)
        delete platform_;

    platform_ = NULL;
}

void application::main(int argc, char *argv[])
{
    //Set up debug logging
    aeon::console::set_loglevel(aeon::console::log_level::debug);

    //Create console streams
    auto console_stdoutput = std::make_shared<aeon::io_stream>
        (aeon::stream::access_mode::write);
    auto console_fileoutput = std::make_shared<aeon::file_stream>
        ("console.log", aeon::stream::access_mode::write);

    //Create listeners with these streams
    auto console_std_listener = 
        std::make_shared<aeon::console_stream_listener>(console_stdoutput);
    auto console_file_listener = 
        std::make_shared<aeon::console_stream_listener>(console_fileoutput);

    //Bind a default console
    aeon::console::add_console_listener(console_std_listener);
    aeon::console::add_console_listener(console_file_listener);

    aeon::configfile config_file;
    config_file.load(std::make_shared<aeon::file_stream>
        ("resources/test.txt", aeon::stream::access_mode::read));

    aeon::root::initialize(std::make_shared<aeon::platforms::glfw>());

    //Register us as a frame listener
    aeon::root::get_singleton().add_frame_listener(this);
    aeon::texture_ptr texture = 
        aeon::texture_manager::get_singleton().load("resources/test.png");

    aeon::root::get_singleton().run();
}

bool application::on_frame(float dt)
{
    return true;
}

bool application::on_render()
{
    return true;
}

} /* namespace aeon */
