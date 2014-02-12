#ifndef AeonMemoryStream_h__
#define AeonMemoryStream_h__

#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class MemoryStream : public Stream
{
public:
	enum class DeleteMode
	{
		None,
		DeleteOnDestruct
	};

	MemoryStream(DeleteMode delete_mode = DeleteMode::DeleteOnDestruct, int access_mode = AccessMode::READ_WRITE);
	MemoryStream(BufferPtr buffer, int access_mode = AccessMode::READ_WRITE);
	MemoryStream(void *buffer, size_t size, DeleteMode delete_mode = DeleteMode::DeleteOnDestruct, int access_mode = AccessMode::READ_WRITE);
	~MemoryStream();

	virtual size_t					read(void *buffer, size_t count);
	virtual size_t					write(const void *buffer, size_t count);

	virtual size_t					read_line(std::string &str);

	virtual bool					seek(size_t pos, SeekDirection direction);
	virtual size_t					tell() const;

	virtual bool					eof() const;

	virtual void					close();

	virtual void					flush();

	virtual bool					good();

	virtual BufferPtr				get_as_buffer();

protected:
	BufferPtr						m_buffer;
	DeleteMode						m_delete_mode;

	size_t							m_buffer_offset;
};

typedef std::shared_ptr<MemoryStream> MemoryStreamPtr;
#define AeonEmptyMemoryStream MemoryStreamPtr;

} //namespace Aeon

#endif // AeonMemoryStream_h__
