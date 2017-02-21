/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/midi.h>

namespace aeon
{
namespace midi
{

auto midi_device::get_port_count() const -> unsigned
{
    return midi_device_.getPortCount();
}

auto midi_device::get_port_name(const unsigned int index) const -> std::string
{
    return midi_device_.getPortName(index);
}

auto midi_device::get_ports() const -> std::vector<std::string>
{
    auto port_count = get_port_count();
    auto ports = std::vector<std::string>(port_count);

    for (auto i = 0ul; i < port_count; ++i)
    {
        ports[i] = get_port_name(i);
    }

    return ports;
}

midi_device::midi_device(RtMidi &midi_device)
    : midi_device_(midi_device)
{
}

midi_device::~midi_device() = default;

} // namespace midi
} // namespace aeon
