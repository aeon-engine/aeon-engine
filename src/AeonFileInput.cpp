#include "Aeon.h"
#include "AeonFileInput.h"
#include "AeonConsole.h"

namespace Aeon
{
namespace File
{

char Input::m_line_buffer[AEON_FILE_LINE_BUFFER_SIZE];

Input::Input()
:
m_file(NULL),
m_size(0),
m_mode(Mode::Binary)
{

}

Input::~Input()
{
	close();
}

bool Input::open(const std::string &path, Mode mode /*= Mode::Binary*/)
{
	return open(path.c_str());
}

bool Input::open(const char *path, Mode mode /*= Mode::Binary*/)
{
	m_mode = mode;
	m_path = path;
	
	//Open the file
	if(mode == Mode::Binary)
		m_file = fopen(path, "rb");
	else
		m_file = fopen(path, "r");

	if (!m_file)
	{
		Console::error("Could not open file: %s", path);
		return false;
	}

	//Determine file size
	if (!seek(0, SeekDirection::End))
	{
		Console::error("Could not determine file size for file: %s. Seek end failed.", path);
		return false;
	}

	m_size = ftell(m_file);

	if (m_size == 0)
	{
		Console::warning("File is empty: %s", path);
	}

	if (!seek(0, SeekDirection::Begin))
	{
		Console::error("Could not determine file size for file: %s. Seek begin failed.", path);
		return false;
	}

	return true;
}

void Input::close()
{
	if (m_file)
		fclose(m_file);

	m_file = NULL;
}

size_t Input::read(unsigned char *buffer)
{
	return read(buffer, m_size);
}

size_t Input::read(unsigned char *buffer, size_t size)
{
	if (!m_file || !buffer)
	{
		Console::error("Could not read from file.");
		return 0;
	}

	if (m_mode == Mode::Text)
	{
		Console::error("Invalid read operation on file '%s'. File was opened as text.", m_path.c_str());
		return 0;
	}

	return fread(buffer, 1, size, m_file);
}

size_t Input::read(std::string &string)
{
	string.reserve(m_size);
	return read((unsigned char *)string.data(), m_size);
}

bool Input::readline(std::string &string)
{
	if (!m_file)
	{
		Console::error("Could not read from file.");
		return false;
	}

	if (m_mode == Mode::Binary)
	{
		Console::error("Invalid read operation on file '%s'. File was opened as binary.", m_path.c_str());
		return false;
	}

	if(fgets(m_line_buffer, AEON_FILE_LINE_BUFFER_SIZE, m_file) == NULL)
	{
		//Only show an error if we're not actually eof.
		if(!eof())
		{
			Console::error("Invalid read operation on file '%s'. Could not read line.", m_path.c_str());
		}
		return false;
	}

	string = m_line_buffer;
	return true;
}

bool Input::seek(size_t count, SeekDirection direction)
{
	switch (direction)
	{
		case SeekDirection::Begin:
		{
			return fseek(m_file, count, SEEK_SET) == 0;
		}break;
		case SeekDirection::Current:
		{
			return fseek(m_file, count, SEEK_CUR) == 0;
		}break;
		case SeekDirection::End:
		{
			return fseek(m_file, count, SEEK_END) == 0;
		}break;
	};

	return false;
}

bool Input::eof()
{
	if(!m_file)
		return true;

	return !(feof(m_file) == 0);
}

} //namespace File
} //namespace Aeon
