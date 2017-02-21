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

midi_input_device::midi_input_device()
    : midi_device(midi_input_device_)
    , midi_input_device_()
    , port_(0)
{
}

midi_input_device::~midi_input_device()
{
    if (midi_input_device_.isPortOpen())
        midi_input_device_.closePort();
}

void midi_input_device::open(const unsigned int port)
{
    port_ = port;
    midi_input_device_.openPort(port);
}

auto midi_input_device::get_message(std::vector<unsigned char> &message) const -> double
{
    return midi_input_device_.getMessage(&message);
}

void midi_input_device::set_message_mask(const int mask)
{
    midi_input_device_.ignoreTypes(utility::check_bit_flag(mask, midi_message_type::system_exclusive),
                                   utility::check_bit_flag(mask, midi_message_type::time_code),
                                   utility::check_bit_flag(mask, midi_message_type::sense));
}

} // namespace midi
} // namespace aeon
