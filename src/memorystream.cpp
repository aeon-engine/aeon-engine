#include "stdafx.h"

namespace aeon
{

memory_stream::memory_stream(
    delete_mode mode /*= delete_mode::delete_on_destruct*/)
:
stream(access_mode::write),
buffer_(std::make_shared<buffer>()),
buffer_offset_(0)
{
    // Set the correct delete mode in our buffer
    buffer_->set_delete_mode(mode == delete_mode::delete_on_destruct ? 
        buffer::delete_mode::delete_on_destruct : buffer::delete_mode::none);
}

memory_stream::memory_stream(buffer_ptr buffer, 
    int mode /*= access_mode::read_write*/)
:
stream(mode),
buffer_(buffer),
buffer_offset_(0)
{

}

memory_stream::memory_stream(const std::string &name, 
    delete_mode mode /*= delete_mode::delete_on_destruct*/)
:
stream(name, access_mode::write),
buffer_(std::make_shared<buffer>()),
buffer_offset_(0)
{
    // Set the correct delete mode in our buffer
    buffer_->set_delete_mode(mode == delete_mode::delete_on_destruct ? 
        buffer::delete_mode::delete_on_destruct : buffer::delete_mode::none);
}

memory_stream::memory_stream(const std::string &name, 
    buffer_ptr buffer, int access_mode /*= access_mode::read_write*/)
:
stream(access_mode),
buffer_(buffer),
buffer_offset_(0)
{

}

memory_stream::~memory_stream()
{

}

size_t memory_stream::read(void *buffer, size_t count)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("MemoryStream: Read on write-only stream.");
        return 0;
    }

    char *data = (char *) buffer_->get();

    if(!data)
    {
        console::error("MemoryStream: Read on empty stream. Buffer was NULL.");
        return 0;
    }

    if(!buffer)
    {
        console::error("MemoryStream: Input buffer is NULL.");
        return 0;
    }

    if(count == 0)
    {
        console::warning("MemoryStream: Tried writing 0 bytes.");
        return 0;
    }

    // Only read what we have
    if(buffer_->size() < buffer_offset_ + count)
        count = buffer_->size() - buffer_offset_;

    // Are we really out of bounds?
    if(count <= 0)
        return 0;

    // Copy our data
    memcpy(buffer, &data[buffer_offset_], count);

    return count;
}

bool memory_stream::read(std::uint8_t &data)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("MemoryStream: Read on write-only stream.");
        return false;
    }

    // Are we trying to read out of bounds?
    if(buffer_->size() >= buffer_offset_)
        return false;

    char *buff = (char *)buffer_->get();
    data = (std::uint8_t) buff[buffer_offset_++];

    return true;
}

bool memory_stream::peek(std::uint8_t &data)
{
    if(!(access_mode_ & access_mode::read))
    {
        console::error("MemoryStream: Peek on write-only stream.");
        return false;
    }

    // Are we trying to read out of bounds?
    if (buffer_->size() >= buffer_offset_)
        return false;

    char *buff = (char *)buffer_->get();
    data = (std::uint8_t) buff[buffer_offset_];

    return true;
}

size_t memory_stream::write(const void *buffer, size_t count)
{
    if(!(access_mode_ & access_mode::write))
    {
        console::error("MemoryStream: WRITE on read-only stream.");
        return 0;
    }

    // Make sure we have enough space in the buffer
    if(!buffer_->reserve(buffer_offset_ + count))
    {
        console::error("MemoryStream: WRITE on stream failed. "
            "Could not reserve memory.");
        return 0;
    }

    // Get our data pointer
    char *data = (char *)buffer_->get();
    
    // Copy our data
    memcpy(&data[buffer_offset_], buffer, count);

    return count;
}

bool memory_stream::seek(size_t pos, seek_direction direction)
{
    size_t new_pos = 0;
    switch(direction)
    {
        case seek_direction::begin:
		    { new_pos = pos; } 
            break;
        case seek_direction::current:
            { new_pos = buffer_offset_ + pos; } 
            break;
        case seek_direction::end:
            { new_pos = buffer_->size() - pos; }
            break;
    };

    // Can't go higher then the size of our buffer...
    if(new_pos >= buffer_->size())
        return false;

    // Set the new offset if all is good
    buffer_offset_ = new_pos;
    return true;
}

size_t memory_stream::tell() const
{
    return buffer_offset_;
}

bool memory_stream::eof() const
{
    return buffer_offset_ >= buffer_->size();
}

void memory_stream::close()
{
    // Create a new buffer, and remove all references to the old one.
    // This may leak memory if DeleteOnDestruct was not set.
    buffer_ = std::make_shared<buffer>();
}

void memory_stream::flush()
{
    // Nothing to do here.
}

bool memory_stream::good()
{
    // Do we have a buffer?
    if(!(buffer_->get() != NULL))
        return false;

    // Are we still within bounds?
    if(buffer_offset_ >= buffer_->size())
        return false;

    // All ok!
    return true;
}

buffer_ptr memory_stream::get_as_buffer()
{
    return buffer_;
}

} /* namespace Aeon */
