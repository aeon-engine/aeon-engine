#ifndef AeonMemoryStream_h__
#define AeonMemoryStream_h__

#include "AeonStream.h"

namespace Aeon
{

class MemoryStream : public Stream
{
public:
	MemoryStream();
	~MemoryStream();

	virtual size_t		read(void *buffer, size_t count);
	virtual size_t		write(const void *buffer, size_t count);

	virtual size_t		read_line(std::string &str);
	virtual size_t		write(const std::string &str);

	virtual bool		seek(size_t pos, SeekDirection direction);
	virtual size_t		tell() const;

	virtual bool		eof() const;

	virtual void		close();

	virtual void		flush();

	virtual bool		good();
};

} //namespace Aeon

#endif // AeonMemoryStream_h__
