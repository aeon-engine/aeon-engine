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

	MemoryStream(DeleteMode delete_mode = DeleteMode::DeleteOnDestruct);
	MemoryStream(BufferPtr buffer, int access_mode = AccessMode::ReadWrite);

	MemoryStream(const std::string &name, DeleteMode delete_mode = DeleteMode::DeleteOnDestruct);
	MemoryStream(const std::string &name, BufferPtr buffer, int access_mode = AccessMode::ReadWrite);

	~MemoryStream();

	virtual size_t					read(void *buffer, size_t count);
	virtual size_t					write(const void *buffer, size_t count);

	virtual bool					read(std::uint8_t &data);
	virtual bool					peek(std::uint8_t &data);

	virtual bool					seek(size_t pos, SeekDirection direction);
	virtual size_t					tell() const;

	virtual bool					eof() const;

	virtual void					close();

	virtual void					flush();

	virtual bool					good();

	virtual BufferPtr				get_as_buffer();

protected:
	BufferPtr						buffer_;
	DeleteMode						delete_mode_;

	size_t							buffer_offset_;
};

typedef std::shared_ptr<MemoryStream> MemoryStreamPtr;
#define AeonEmptyMemoryStream MemoryStreamPtr;

} /* namespace Aeon */

#endif /* AeonMemoryStream_h__ */
