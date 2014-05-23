#ifndef iostream_h__
#define iostream_h__

#include "aeon/streams/stream.h"

namespace aeon
{

class io_stream : public stream
{
public:
	io_stream(int mode = access_mode::read);
	io_stream(const std::string &name, int mode = access_mode::read);

	virtual size_t					read(void *buffer, size_t count);
	virtual size_t					write(const void *buffer, size_t count);

	virtual bool					read(std::uint8_t &data);
	virtual bool					peek(std::uint8_t &data);

	virtual bool					seek(size_t pos, seek_direction direction);
	virtual size_t					tell() const;

	virtual bool					eof() const;

	virtual void					flush();

	virtual bool					good() { return true; }

	virtual buffer_ptr				get_as_buffer();
};

} //namespace aeon

#endif // iostream_h__
