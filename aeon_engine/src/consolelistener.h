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

} // namespace aeon

#endif // consolelistener_h__
