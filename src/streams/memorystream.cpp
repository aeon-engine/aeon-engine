#include "Aeon/Aeon.h"
#include "Aeon/Streams/MemoryStream.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

MemoryStream::MemoryStream(DeleteMode delete_mode /*= DeleteMode::DeleteOnDestruct*/)
:
Stream(AccessMode::Write),
buffer_(std::make_shared<Buffer>()),
buffer_offset_(0)
{
	//Set the correct delete mode in our buffer
	buffer_->set_delete_mode(delete_mode == DeleteMode::DeleteOnDestruct ? Buffer::DeleteMode::DeleteOnDestruct : Buffer::DeleteMode::None);
}

MemoryStream::MemoryStream(BufferPtr buffer, int access_mode /*= AccessMode::ReadWrite*/)
:
Stream(access_mode),
buffer_(buffer),
buffer_offset_(0)
{

}

MemoryStream::MemoryStream(const std::string &name, DeleteMode delete_mode /*= DeleteMode::DeleteOnDestruct*/)
:
Stream(name, AccessMode::Write),
buffer_(std::make_shared<Buffer>()),
buffer_offset_(0)
{
	//Set the correct delete mode in our buffer
	buffer_->set_delete_mode(delete_mode == DeleteMode::DeleteOnDestruct ? Buffer::DeleteMode::DeleteOnDestruct : Buffer::DeleteMode::None);
}

MemoryStream::MemoryStream(const std::string &name, BufferPtr buffer, int access_mode /*= AccessMode::ReadWrite*/)
:
Stream(access_mode),
buffer_(buffer),
buffer_offset_(0)
{

}

MemoryStream::~MemoryStream()
{

}

size_t MemoryStream::read(void *buffer, size_t count)
{
	if(!(access_mode_ & AccessMode::Read))
	{
		Console::error("MemoryStream: Read on write-only stream.");
		return 0;
	}

	char *data = (char *) buffer_->get();

	if(!data)
	{
		Console::error("MemoryStream: Read on empty stream. Buffer was NULL.");
		return 0;
	}

	if(!buffer)
	{
		Console::error("MemoryStream: Input buffer is NULL.");
		return 0;
	}

	if(count == 0)
	{
		Console::warning("MemoryStream: Tried writing 0 bytes.");
		return 0;
	}

	//Only read what we have
	if(buffer_->size() < buffer_offset_ + count)
		count = buffer_->size() - buffer_offset_;

	//Are we really out of bounds?
	if(count <= 0)
		return 0;

	//Copy our data
	memcpy(buffer, &data[buffer_offset_], count);

	return count;
}

bool MemoryStream::read(std::uint8_t &data)
{
	if(!(access_mode_ & AccessMode::Read))
	{
		Console::error("MemoryStream: Read on write-only stream.");
		return false;
	}

	//Are we trying to read out of bounds?
	if(buffer_->size() >= buffer_offset_)
		return false;

	char *buff = (char *)buffer_->get();
	data = (std::uint8_t) buff[buffer_offset_++];

	return true;
}

bool MemoryStream::peek(std::uint8_t &data)
{
	if(!(access_mode_ & AccessMode::Read))
	{
		Console::error("MemoryStream: Peek on write-only stream.");
		return false;
	}

	//Are we trying to read out of bounds?
	if (buffer_->size() >= buffer_offset_)
		return false;

	char *buff = (char *)buffer_->get();
	data = (std::uint8_t) buff[buffer_offset_];

	return true;
}

size_t MemoryStream::write(const void *buffer, size_t count)
{
	if(!(access_mode_ & AccessMode::Write))
	{
		Console::error("MemoryStream: WRITE on read-only stream.");
		return 0;
	}

	//Make sure we have enough space in the buffer
	if(!buffer_->reserve(buffer_offset_ + count))
	{
		Console::error("MemoryStream: WRITE on stream failed. Could not reserve memory.");
		return 0;
	}

	//Get our data pointer
	char *data = (char *)buffer_->get();
	
	//Copy our data
	memcpy(&data[buffer_offset_], buffer, count);

	return count;
}

bool MemoryStream::seek(size_t pos, SeekDirection direction)
{
	size_t new_pos = 0;
	switch(direction)
	{
		case SeekDirection::Begin:		{ new_pos = pos; } break;
		case SeekDirection::Current:	{ new_pos = buffer_offset_ + pos; } break;
		case SeekDirection::End:		{ new_pos = buffer_->size() - pos; } break;
	};

	//Can't go higher then the size of our buffer...
	if(new_pos >= buffer_->size())
		return false;

	//Set the new offset if all is good
	buffer_offset_ = new_pos;
	return true;
}

size_t MemoryStream::tell() const
{
	return buffer_offset_;
}

bool MemoryStream::eof() const
{
	return buffer_offset_ >= buffer_->size();
}

void MemoryStream::close()
{
	//Create a new buffer, and remove all references to the old one.
	//This may leak memory if DeleteOnDestruct was not set.
	buffer_ = std::make_shared<Buffer>();
}

void MemoryStream::flush()
{
	//Nothing to do here.
}

bool MemoryStream::good()
{
	//Do we have a buffer?
	if(!(buffer_->get() != NULL))
		return false;

	//Are we still within bounds?
	if(buffer_offset_ >= buffer_->size())
		return false;

	//All ok!
	return true;
}

BufferPtr MemoryStream::get_as_buffer()
{
	return buffer_;
}

} /* namespace Aeon */
