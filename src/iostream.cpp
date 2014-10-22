#include "stdafx.h"

namespace aeon
{

io_stream::io_stream(int mode /*= access_mode::read*/)
:
stream(mode)
{

}

io_stream::io_stream(const std::string &name, int mode /*= access_mode::read*/)
:
stream(name, mode)
{

}

size_t io_stream::read(void *buffer, size_t count)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("IOStream: Read on write-only stream.");
        return 0;
    }

    if(!buffer)
    {
        console::error("IOStream: Input buffer is NULL.");
        return 0;
    }

    if(count == 0)
    {
        console::warning("IOStream: Tried writing 0 bytes.");
        return 0;
    }

    return fread(buffer, 1, count, stdin);
}

bool io_stream::read(std::uint8_t &data)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("IOStream: Read on write-only stream.");
        return false;
    }

    int c = fgetc(stdin);

    if(c == EOF)
        return false;

    data = (std::uint8_t) c;
    return true;
}

bool io_stream::peek(std::uint8_t &data)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("IOStream: Peek on write-only stream.");
        return false;
    }

    int c = fgetc(stdin);

    if(c == EOF)
        return false;

    // TODO: research if there is a good alternative for this.
    if(ungetc(c, stdin) == EOF)
        return false;

    data = (std::uint8_t) c;
    return true;
}

size_t io_stream::write(const void *buffer, size_t count)
{
    if(access_mode_ != access_mode::write)
    {
        console::error("IOStream: Write on read-only stream.");
        return 0;
    }

    if(!buffer)
    {
        console::error("IOStream: Input buffer is NULL.");
        return 0;
    }

    if(count == 0)
    {
        console::warning("IOStream: Tried writing 0 bytes.");
        return 0;
    }

    return fwrite(buffer, 1, count, stdout);
}

bool io_stream::seek(size_t pos, seek_direction direction)
{
    AEON_UNUSED(pos);
    AEON_UNUSED(direction);

    // This won't work for STDIN...
    return false;
}

size_t io_stream::tell() const
{
    // This won't work for STDIN...
    return 0;
}

bool io_stream::eof() const
{
    return (feof(stdin) != 0);
}

void io_stream::flush()
{
    fflush(stdout);
}

aeon::buffer_ptr io_stream::get_as_buffer()
{
    // This won't work for STDIN...
    return aeon_empty_buffer;
}

} /* namespace aeon */
