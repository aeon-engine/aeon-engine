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

#include <application.h>
#include <parser.h>
#include <generator.h>

namespace aeon
{
namespace serialization
{

auto application::main(int, char *[]) -> int
{
    parser p;
    auto objects = p.parse_object_files();

    generator g;
    g.generate_code(objects);

    return 0;
}

} // namespace serialization
} // namespace aeon
