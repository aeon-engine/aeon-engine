#include "aeon/stdafx.h"

namespace aeon
{

stream::stream(int mode /*= access_mode::read*/)
:
has_name_(false),
name_(AEON_STREAM_DEFAULT_NAME),
size_(0),
access_mode_(mode)
{}

stream::stream(const std::string &name, int mode /*= access_mode::read*/)
:
has_name_(true),
name_(name),
size_(0),
access_mode_(mode)
{}

stream::~stream()
{
    close();
}

buffer_ptr stream::get_as_buffer()
{
    size_t s = size();
    
    auto buff = std::make_shared<buffer>(s);
    read(buff->get(), s);

    return buff;
}

size_t stream::write(const std::string &str)
{
    return write(str.data(), str.size());
}

size_t stream::write(buffer_ptr buffer)
{
    if(!buffer)
    {
        console::error("Stream: Tried writing an empty buffer to a stream.");
        return 0;
    }

    return write(buffer->get(), buffer->size());
}

size_t stream::read_line(std::string &str)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("Stream: Read on write-only stream.");
        return 0;
    }

    std::uint8_t c = 0;
    bool result = true;

    std::string line;
    for (int i = 0; i < AEON_STREAM_MAX_TEXT_LINE_LENGTH; ++i)
    {
        // Read a character
        result = read(c);

        // Could we read anything?
        if(!result)
            break;

        // Check if it's a line-ending character
        if(c == '\n')
        {
            // Peek if the next character is a '\r'
            result = peek(c);

            // If it's '\r', then we should seek 1 byte ahead
            if (result && c == '\r')
                seek(1, seek_direction::current);

            break;
        }

        // Check if it's a line-ending character
        if(c == '\r')
        {
            // Peek if the next character is a '\n'
            result = peek(c);

            // If it's '\n', then we should seek 1 byte ahead
            if (result && c == '\n')
                seek(1, seek_direction::current);

            break;
        }

        line += c;
    }

    str = line;

    return line.length();
}

} /* namespace aeon */
