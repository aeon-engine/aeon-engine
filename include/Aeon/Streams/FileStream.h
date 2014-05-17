#ifndef AeonFileStream_h__
#define AeonFileStream_h__

#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class FileStream : public Stream
{
public:
	FileStream(const std::string &path, int access_mode = AccessMode::Read);
	virtual ~FileStream();

	virtual size_t		read(void *buffer, size_t count);
	virtual size_t		write(const void *buffer, size_t count);

	virtual bool		read(std::uint8_t &data);
	virtual bool		peek(std::uint8_t &data);

	virtual bool		seek(size_t pos, SeekDirection direction);
	virtual size_t		tell() const;

	virtual bool		eof() const;

	virtual void		close();

	virtual void		flush();

	virtual bool		good();

protected:
	void				__open_file();
	void				__calculate_file_size();

	FILE *				file_;
};

typedef std::shared_ptr<FileStream> FileStreamPtr;

} //namespace Aeon

#endif /* AeonFileStream_h__ */
