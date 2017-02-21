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
#include <aeon/streams.h>
#include <aeon/utility.h>

namespace aeon
{
namespace midi
{

namespace meta_event
{
static const unsigned char sequence_number = 0x00;
static const unsigned char text_event = 0x01;
static const unsigned char copyright_notice = 0x02;
static const unsigned char track_name = 0x03;
static const unsigned char instrument_name = 0x04;
static const unsigned char lyric_text = 0x05;
static const unsigned char marker_text = 0x06;
static const unsigned char cue_point = 0x07;
static const unsigned char channel_prefix_assignment = 0x20;
static const unsigned char end_of_track = 0x2F;
static const unsigned char tempo_setting = 0x51;
static const unsigned char smpte_offset = 0x54;
static const unsigned char time_signature = 0x58;
static const unsigned char key_signature = 0x59;
static const unsigned char sequencer_specific = 0x7F;
} // namespace meta_event

midi_file_reader::midi_file_reader(const std::string &filename)
    : format_(midi_format::format0)
    , tracks_(0)
    , tempo_mode_(midi_tempo_mode::ppqn)
    , divisions_(0)
{
    read_file(filename);
}

midi_file_reader::~midi_file_reader()
{
}

void midi_file_reader::read_file(const std::string &filename)
{
    streams::file_stream file_stream(filename, streams::access_mode::read, streams::file_mode::binary);
    auto midi_data = file_stream.read_to_vector();
    streams::memory_stream memory_stream(std::move(midi_data), streams::access_mode::read);

    read_header(memory_stream);
    read_all_track_chunks(memory_stream);
}

void midi_file_reader::read_header(streams::memory_stream &stream)
{
    streams::stream_reader<streams::memory_stream> reader(stream);

    std::uint32_t mthd = 0;
    reader >> mthd;

    if (utility::endianness::swap32(mthd) != 'MThd')
        throw std::runtime_error("Invalid or corrupt midi file. MThd not found.");

    std::uint32_t header_length = 0;
    reader >> header_length;
    header_length = utility::endianness::swap32(header_length);

    if (header_length != 6)
        throw std::runtime_error("Invalid or corrupt midi file. Header length is expected to be 6.");

    std::uint16_t format = 0;
    reader >> format;
    parse_format(utility::endianness::swap16(format));

    std::uint16_t tracks = 0;
    reader >> tracks;
    tracks_ = utility::endianness::swap16(tracks);

    std::uint16_t divisions = 0;
    reader >> divisions;
    parse_divisions(utility::endianness::swap16(divisions));
}

void midi_file_reader::parse_format(const std::uint16_t format)
{
    switch (format)
    {
        case 0:
            format_ = midi_format::format0;
            return;
        case 1:
            format_ = midi_format::format1;
            return;
        case 2:
            format_ = midi_format::format2;
            throw std::runtime_error("Midi format 2 is untested.");
            return;
        default:
            break;
    }

    throw std::runtime_error("Invalid or corrupt midi file. Format must be 0, 1 or 2.");
}

void midi_file_reader::parse_divisions(const std::uint16_t divisions)
{
    // If bit 0x80 is not set, the midi file uses ppqn mode; otherwise smpte.
    if (!utility::check_bit_flag<std::uint16_t>(divisions, 0x8000))
    {
        tempo_mode_ = midi_tempo_mode::ppqn;
        divisions_ = divisions;
    }
    else
    {
        tempo_mode_ = midi_tempo_mode::smpte;
        throw std::runtime_error("SMPTE is untested.");
    }
}

void midi_file_reader::read_all_track_chunks(streams::memory_stream &stream)
{
    for (auto i = 0u; i < tracks_; ++i)
    {
        read_next_track_chunk(stream);
    }
}

void midi_file_reader::read_next_track_chunk(streams::memory_stream &stream)
{
    auto track_length = read_track_header(stream);

    std::vector<std::uint8_t> track_data;
    auto result = stream.vector_read(track_data, track_length);

    if (result != track_length)
        throw std::runtime_error("Could not read track data!");

    streams::memory_stream memory_stream(std::move(track_data), streams::access_mode::read);
    parse_track_data(memory_stream);
}

std::uint32_t midi_file_reader::read_track_header(streams::memory_stream &stream) const
{
    streams::stream_reader<streams::memory_stream> reader(stream);

    std::uint32_t mtrk = 0;
    reader >> mtrk;

    if (utility::endianness::swap32(mtrk) != 'MTrk')
        throw std::runtime_error("Invalid or corrupt midi file. MTrk not found.");

    std::uint32_t track_length = 0;
    reader >> track_length;
    return utility::endianness::swap32(track_length);
}

void midi_file_reader::parse_track_data(streams::memory_stream &stream)
{
    streams::stream_reader<streams::memory_stream> reader(stream);

    while (!stream.eof())
    {
        std::uint32_t vtime = read_vtime(stream);
        std::uint8_t event = 0;
        reader >> event;

        (void)vtime;
        if (event == messages::meta)
        {
            parse_meta_event(stream);
        }
        else if (event == messages::system_exclusive || event == messages::end_of_exclusive)
        {
            parse_sysex_event(stream);
        }
        else
        {
            parse_midi_event(stream, event);
        }
    }
}

std::uint32_t midi_file_reader::read_vtime(streams::memory_stream &stream)
{
    streams::stream_reader<streams::memory_stream> reader(stream);

    std::uint8_t value_part;
    reader >> value_part;

    std::uint32_t value = value_part & ~0x80;

    while (utility::check_bit_flag<std::uint8_t>(value_part, 0x80))
    {
        reader >> value_part;
        value = (value << 7);
        value += value_part & ~0x80;
    }

    return value;
}

void midi_file_reader::parse_meta_event(streams::memory_stream &stream)
{
    streams::stream_reader<streams::memory_stream> reader(stream);
    std::uint8_t meta_type = 0;
    reader >> meta_type;

    std::uint32_t metadata_length = read_vtime(stream);

    if (metadata_length == 0)
        return;

    std::vector<std::uint8_t> metadata;
    auto result = stream.vector_read(metadata, metadata_length);

    if (result != metadata_length)
        throw std::runtime_error("Invalid or corrupt midi file. Could not read metadata.");
}

void midi_file_reader::parse_sysex_event(streams::memory_stream &stream)
{
    std::uint32_t sysex_length = read_vtime(stream);

    if (sysex_length == 0)
        return;

    std::vector<std::uint8_t> sysex_data;
    auto result = stream.vector_read(sysex_data, sysex_length);

    if (result != sysex_length)
        throw std::runtime_error("Invalid or corrupt midi file. Could not read sysex data.");
}

void midi_file_reader::parse_midi_event(streams::memory_stream &stream, const std::uint8_t message)
{
    streams::stream_reader<streams::memory_stream> reader(stream);

    if ((message & 0xF0) == messages::note_off)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t velocity = 0;
        reader >> velocity;
    }
    else if ((message & 0xF0) == messages::note_on)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t velocity = 0;
        reader >> velocity;
    }
    else if ((message & 0xF0) == messages::polyphonic_key_pressure)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t pressure = 0;
        reader >> pressure;
    }
    else if ((message & 0xF0) == messages::controller_change)
    {
        std::uint8_t controller_number = 0;
        reader >> controller_number;

        std::uint8_t controller_value = 0;
        reader >> controller_value;
    }
    else if ((message & 0xF0) == messages::program_change)
    {
        std::uint8_t program_number = 0;
        reader >> program_number;
    }
    else if ((message & 0xF0) == messages::channel_pressure)
    {
        std::uint8_t pressure = 0;
        reader >> pressure;
    }
    else if ((message & 0xF0) == messages::pitch_bend)
    {
        std::uint8_t value_lsb = 0;
        reader >> value_lsb;

        std::uint8_t value_msb = 0;
        reader >> value_msb;
    }
    else
    {
        std::uint8_t message2 = 0;
        reader >> message2;

        std::runtime_error("Invalid or corrupt midi file. Unexpected midi message.");
    }
}

} // namespace midi
} // namespace aeon
