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
#include <algorithm>

namespace aeon
{
namespace midi
{

static const int receive_buffer_reserve_size = 16;
static const int notes_pressed_reserve_size = 16;

midi_input_manager::midi_input_manager(midi_input_device &device)
    : input_device_(device)
    , receive_buffer_()
    , notes_()
{
    receive_buffer_.reserve(receive_buffer_reserve_size);

    for (auto &n : notes_)
        n.reserve(notes_pressed_reserve_size);
}

midi_input_manager::~midi_input_manager() = default;

void midi_input_manager::run_one()
{
    auto time_code = input_device_.get_message(receive_buffer_);

    if (receive_buffer_.empty())
        return;

    __parse_note_data(receive_buffer_);

    for (auto listener : listeners_)
    {
        listener->on_midi_input(*this, receive_buffer_, time_code);
    }
}

void midi_input_manager::__parse_note_data(const std::vector<unsigned char> &data)
{
    auto message = data[0];
    if ((message & 0xF0) == messages::note_on)
    {
        auto note_info = midi_note_parser(data);
        notes_[note_info.channel].push_back(midi_note(note_info));
    }
    else if ((message & 0xF0) == messages::note_off)
    {
        auto note_info = midi_note_parser(data);
        auto &note_vector = notes_[note_info.channel];

        note_vector.erase(std::remove_if(note_vector.begin(), note_vector.end(),
                                         [&note_info](const midi_note &note) { return note.note == note_info.note; }),
                          note_vector.end());
    }
}

} // namespace midi
} // namespace aeon
