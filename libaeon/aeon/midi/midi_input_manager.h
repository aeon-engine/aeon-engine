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

static const int max_midi_channels = 16;

struct midi_note_parser
{
    explicit midi_note_parser(const std::vector<unsigned char> &buffer)
        : message(buffer[0])
        , channel(utility::get_low_nibble(message))
        , note(buffer[1])
        , velocity(buffer[2])
    {
    }

    unsigned char message;
    unsigned char channel;
    unsigned char note;
    unsigned char velocity;
};

struct midi_note
{
    explicit midi_note(const midi_note_parser &parser)
        : note(parser.note)
        , velocity(parser.velocity)
    {
    }

    explicit midi_note(const unsigned char note, const unsigned char velocity)
        : note(note)
        , velocity(velocity)
    {
    }

    unsigned char note;
    unsigned char velocity;
};

class midi_input_manager;

class midi_input_listener
{
public:
    midi_input_listener() = default;
    virtual ~midi_input_listener() = default;

    virtual void on_midi_input(midi_input_manager &manager, const std::vector<unsigned char> &data,
                               const double time_code) = 0;
};

class midi_input_manager : public utility::listener_subject<midi_input_listener>
{
public:
    explicit midi_input_manager(midi_input_device &device);
    ~midi_input_manager();

    void run_one();

    auto &get_input_device()
    {
        return input_device_;
    }

    const auto &get_pressed_notes(const unsigned int channel) const
    {
        assert(channel < max_midi_channels);
        return notes_[channel];
    }

private:
    void __parse_note_data(const std::vector<unsigned char> &data);

    midi_input_device &input_device_;
    std::vector<unsigned char> receive_buffer_;

    std::array<std::vector<midi_note>, max_midi_channels> notes_;
};

} // namespace midi
} // namespace aeon
