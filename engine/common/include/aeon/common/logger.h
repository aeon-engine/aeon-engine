/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#pragma once

#include <aeon/logger.h>
#include <aeon/utility.h>
#include <aeon/streams.h>

namespace aeon
{
namespace common
{

/*!
 * This class is the main aeon engine logger. Every subsystem will log through this class.
 */
class logger : public aeon::logger::simple_sink_backend, public utility::singleton<logger>
{
public:
    /*!
     * Constructor
     */
    logger();

    /*!
     * Destructor
     */
    virtual ~logger();

private:
    streams::io_stream io_stream_;
    aeon::logger::io_stream_sink stream_sink_;
};

} // namespace common
} // namespace aeon
