#ifndef AeonFileInput_h__
#define AeonFileInput_h__

#include "AeonFile.h"

namespace Aeon
{
namespace File
{

//TODO: For now only binary files. Support text and binary in a neat interface.
class Input
{
public:
	Input();
	~Input();

	bool				open(const std::string &path, Mode mode = Mode::Binary);
	bool				open(const char *path, Mode mode = Mode::Binary);
	void				close();

	size_t				read(unsigned char *buffer);
	size_t				read(unsigned char *buffer, size_t size);
	size_t				read(std::string &string);

	bool				readline(std::string &string);

	bool				seek(size_t count, SeekDirection direction);

	size_t				size()				{ return m_size; }

	FILE *				get_descriptor()	{ return m_file; }

	bool				eof();

private:
	FILE *				m_file;
	size_t				m_size;
	Mode				m_mode;
	std::string			m_path;

	static char			m_line_buffer[AEON_FILE_LINE_BUFFER_SIZE];
};

} //namespace File
} //namespace Aeon

#endif // AeonFileInput_h__
