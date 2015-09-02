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

#ifndef console_h__
#define console_h__

namespace aeon
{

class console_listener;
typedef std::shared_ptr<console_listener> console_listener_ptr;

namespace console
{

typedef std::set<console_listener_ptr> console_listeners;

enum class log_level : int
{
    error    = 1,
    warning  = 2,
    info     = 3,
    debug    = 99
};

void error(const char *format, ...);
void warning(const char *format, ...);
void info(const char *format, ...);
void debug(const char *format, ...);

void set_loglevel(log_level level);
log_level get_loglevel();

void add_console_listener(console_listener_ptr listener);
void remove_console_listener(console_listener_ptr listener);
void remove_all_console_listeners();

} // namespace console
} // namespace aeon

#endif // console_h__
