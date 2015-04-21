/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#include "stdafx.h"

namespace aeon
{

console_stream_listener::console_stream_listener(aeon::streams::stream_ptr stream) :
    stream_(stream)
{

}

console_stream_listener::~console_stream_listener()
{

}

void console_stream_listener::on_log_message(double time_diff,
                                             console::log_level level,
                                             const std::string &message)
{
    if (!stream_)
        return;

    std::string time_string = aeon::string_utils::float_to_string(
        (float) time_diff, 10) + ' ';

    aeon::streams::stream_writer stream_writer(*stream_);

    stream_writer << time_string;

    switch (level)
    {
        case console::log_level::error:
        {
            stream_writer << "[ERR] ";
        }break;
        case console::log_level::warning:
        {
            stream_writer << "[WRN] ";
        }break;
        case console::log_level::info:
        {
            stream_writer << "[INF] ";
        }break;
        case console::log_level::debug:
        {
            stream_writer << "[DBG] ";
        }break;
    }

    stream_writer << message;
    stream_writer << "\n";
}

} // namespace aeon
