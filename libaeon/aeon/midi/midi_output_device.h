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

#pragma once

namespace aeon
{
namespace midi
{

class midi_output_device : public midi_device
{
public:
    midi_output_device();
    virtual ~midi_output_device();

    void open(const unsigned int port);
    void open_virtual(const std::string &name);

    void send_message(std::vector<unsigned char> &message);

    void send_note_off(unsigned char channel, unsigned char note, unsigned char velocity)
    {
        assert(channel <= 15);
        send_note_message(messages::note_off + channel, note, velocity);
    }

    void send_note_on(unsigned char channel, unsigned char note, unsigned char velocity)
    {
        assert(channel <= 15);
        send_note_message(messages::note_on + channel, note, velocity);
    }

private:
    void send_note_message(unsigned char message, unsigned char note, unsigned char velocity)
    {
        assert(note <= 127);
        assert(velocity <= 127);

        auto data = note_output_buffer_.data();
        data[0] = message;
        data[1] = note;
        data[2] = velocity;
        midi_output_device_.sendMessage(&note_output_buffer_);
    }

    RtMidiOut midi_output_device_;
    std::vector<unsigned char> note_output_buffer_;
};

} // namespace midi
} // namespace aeon
