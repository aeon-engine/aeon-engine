#ifndef memorystream_h__
#define memorystream_h__

#include "aeon/streams/stream.h"

namespace aeon
{

class memory_stream : public stream
{
public:
	enum class delete_mode
	{
		none,
		delete_on_destruct
	};

	memory_stream(delete_mode delete_mode = delete_mode::delete_on_destruct);
	memory_stream(buffer_ptr buffer, int mode = access_mode::read_write);

	memory_stream(const std::string &name, 
		delete_mode delete_mode = delete_mode::delete_on_destruct);
	memory_stream(const std::string &name, buffer_ptr buffer, 
		int mode = access_mode::read_write);

	~memory_stream();

	virtual size_t read(void *buffer, size_t count);
	virtual size_t write(const void *buffer, size_t count);

	virtual bool read(std::uint8_t &data);
	virtual bool peek(std::uint8_t &data);

	virtual bool seek(size_t pos, seek_direction direction);
	virtual size_t tell() const;

	virtual bool eof() const;

	virtual void close();

	virtual void flush();

	virtual bool good();

	virtual buffer_ptr get_as_buffer();

protected:
	buffer_ptr buffer_;
	delete_mode delete_mode_;

	size_t buffer_offset_;
};

typedef std::shared_ptr<memory_stream> memory_stream_ptr;
#define aeon_empty_memory_stream memory_stream_ptr;

} //namespace Aeon

#endif // memorystream_h__
