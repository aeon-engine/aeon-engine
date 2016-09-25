/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#include <aeon/common/logger.h>

aeon_utility_initialize_singleton(aeon::common::logger);

namespace aeon
{
namespace common
{

logger::logger()
    : aeon::logger::simple_sink_backend(aeon::logger::log_level::trace)
    , stream_sink_(io_stream_)
{
    add_sink(&stream_sink_);
}

logger::~logger()
{
    remove_all_sinks();
}

} // namespace common
} // namespace aeon
