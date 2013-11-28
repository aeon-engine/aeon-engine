#include "Aeon.h"
#include "AeonFileInput.h"
#include "AeonConsole.h"

namespace Aeon
{

FileInput::FileInput()
:
m_file(NULL),
m_file_size(0)
{

}

FileInput::~FileInput()
{
	close();
}

bool FileInput::open(const char *path)
{
	//Open the file
	m_file = fopen(path, "rb");

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

	m_file_size = ftell(m_file);

	if (m_file_size == 0)
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

void FileInput::close()
{
	if (m_file)
		fclose(m_file);

	m_file = NULL;
}

size_t FileInput::read(unsigned char *buffer)
{
	return read(buffer, m_file_size);
}

size_t FileInput::read(unsigned char *buffer, size_t size)
{
	if (!m_file || !buffer)
	{
		Console::error("Could not read from file.");
		return 0;
	}

	return fread(buffer, 1, size, m_file);
}

size_t FileInput::read(std::string &string)
{
	string.reserve(m_file_size);
	return read((unsigned char *)string.data(), m_file_size);
}

bool FileInput::seek(size_t count, SeekDirection direction)
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

} //namespace Aeon
