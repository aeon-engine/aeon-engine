/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/utility.h>
#include <common/application.h>
#include <console/console.h>

namespace aeon
{

application::application()
{
}

application::~application()
{
}

void application::main(int argc, char *argv[])
{
    __setup_console();

    aeon::utility::configfile config_file;
    std::string config_file_path = "config.ini";
    config_file.load(std::make_shared<aeon::streams::file_stream>(config_file_path));
}

void application::__setup_console()
{
    //Set up debug logging
    aeon::console::set_loglevel(aeon::console::log_level::debug);

    //Create console streams
    auto console_stdoutput = std::make_shared<aeon::streams::io_stream>
        (aeon::streams::access_mode::write);

    //console_stdoutput->set_color(aeon::streams::color::blue, aeon::streams::weight::bold);

    std::string console_log_file = "console.log";
    auto console_fileoutput = std::make_shared<aeon::streams::file_stream>
        (console_log_file, aeon::streams::access_mode::write);

    //Create listeners with these streams
    //auto console_std_listener =
    //    std::make_shared<aeon::console_stream_listener>(console_stdoutput);
    //auto console_file_listener =
    //    std::make_shared<aeon::console_stream_listener>(console_fileoutput);

    //Bind a default console
    //aeon::console::add_console_listener(console_std_listener);
    //aeon::console::add_console_listener(console_file_listener);
}

} // namespace aeon