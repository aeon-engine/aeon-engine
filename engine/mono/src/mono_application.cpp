/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/mono/mono_application.h>
#include <aeon/mono/mono_exceptions.h>
#include <aeon/common/logger.h>

#define AEON_DEFAULT_MONO_ASSEMBLY_NAME "MonoGame.dll"

namespace aeon
{
namespace mono
{

mono_application::mono_application(application::context context)
    : desktop_application(std::move(context))
    , logger_(common::logger::get_singleton(), "Mono::Application")
    , jit_manager_(*this)
{
    AEON_LOG_DEBUG(logger_) << "Mono application started." << std::endl;
}

mono_application::~mono_application() = default;

auto mono_application::main(int argc, char *argv[]) -> int
{
    if (argc != 1 && argc != 2)
    {
        AEON_LOG_FATAL(logger_) << "Usage: mono_application [assembly_name]." << std::endl;
        throw mono_script_exception();
    }

    std::string assembly_name = AEON_DEFAULT_MONO_ASSEMBLY_NAME;

    if (argc == 2)
    {
        assembly_name = argv[1];
    }

    jit_manager_.load_assembly(assembly_name);

    try
    {
        jit_manager_.call_initialize();
    }
    catch (const mono_thunk_exception &e)
    {
        AEON_LOG_FATAL(logger_) << "Mono exception: " << e.message() << "\nCallstack: " << e.stacktrace() << std::endl;
        throw;
    }

    get_main_window().attach_listener(this);

    get_platform().run();

    // TODO: Handle return value (capture exceptions from mono?)
    return 0;
}

auto mono_application::on_frame_begin(const float dt) -> bool
{
    try
    {
        return jit_manager_.call_update(dt);
    }
    catch (const mono_thunk_exception &e)
    {
        AEON_LOG_FATAL(logger_) << "Mono exception: " << e.message() << "\nCallstack: " << e.stacktrace() << std::endl;
        throw;
    }
}

} // namespace mono
} // namespace aeon
