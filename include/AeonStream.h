#ifndef AeonDataStream_h__
#define AeonDataStream_h__

#include "AeonBuffer.h"

namespace Aeon
{

class Stream
{
public:
	class AccessMode //Workaround for enum classes not supporting bitflags
	{
	public:
		enum
		{
			READ			= 1,
			WRITE			= 2,
			READ_WRITE		= 3
		};
	};

	enum class SeekDirection
	{
		Begin,
		Current,
		End
	};

	Stream(int access_mode = AccessMode::READ);
	Stream(const std::string &name, int access_mode = AccessMode::READ);

	virtual ~Stream();

	const std::string &				get_name() { return m_name; }
	virtual int						get_access_mode() { return m_access_mode; }

	virtual bool					is_readable() const { return (m_access_mode & AccessMode::READ) != 0; }
	virtual bool					is_writeable() const { return (m_access_mode & AccessMode::WRITE) != 0; }

	virtual size_t					read(void *buffer, size_t count) = 0;
	virtual size_t					write(const void *buffer, size_t count) = 0;

	virtual size_t					read_line(std::string &str) = 0;
	virtual size_t					write(const std::string &str);

	virtual bool					seek(size_t pos, SeekDirection direction) = 0;
	virtual size_t					tell() const = 0;

	virtual bool					eof() const = 0;

	size_t							size() const { return m_size; }
	virtual void					close() {}

	virtual void					flush() {}

	virtual bool					good() { return false; }

	virtual BufferPtr				get_as_buffer();

protected:
	std::string						m_name;
	size_t							m_size;
	int								m_access_mode;
};

typedef std::shared_ptr<Stream> StreamPtr;

} //namespace Aeon

#endif // AeonDataStream_h__
