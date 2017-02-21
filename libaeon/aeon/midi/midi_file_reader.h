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

namespace streams
{
class memory_stream;
}

namespace midi
{

enum class midi_read_mode
{
    normal,      // Keep the midi data as-is
    split_tracks // Split format 0 track data
};

enum class midi_format
{
    format0,
    format1,
    format2
};

enum class midi_tempo_mode
{
    ppqn, // Pulses per quarter note
    smpte // SMPTE time codes
};

class midi_file_reader
{
public:
    explicit midi_file_reader(const std::string &filename);
    virtual ~midi_file_reader();

    auto get_format() const
    {
        return format_;
    }

    auto get_track_count() const
    {
        return tracks_;
    }

    auto get_tempo_mode() const
    {
        return tempo_mode_;
    }

    auto get_divisions() const
    {
        return divisions_;
    }

protected:
    // Ctor for unittesting
    midi_file_reader() = default;

    void read_file(const std::string &filename);

    void read_header(streams::memory_stream &stream);
    void parse_format(const std::uint16_t format);
    void parse_divisions(const std::uint16_t divisions);

    void read_all_track_chunks(streams::memory_stream &stream);
    void read_next_track_chunk(streams::memory_stream &stream);
    std::uint32_t read_track_header(streams::memory_stream &stream) const;
    void parse_track_data(streams::memory_stream &stream);
    std::uint32_t read_vtime(streams::memory_stream &stream);

    void parse_meta_event(streams::memory_stream &stream);
    void parse_sysex_event(streams::memory_stream &stream);
    void parse_midi_event(streams::memory_stream &stream, const std::uint8_t message);

    midi_format format_;
    unsigned int tracks_;

    midi_tempo_mode tempo_mode_;
    unsigned int divisions_;
};

} // namespace midi
} // namespace aeon
