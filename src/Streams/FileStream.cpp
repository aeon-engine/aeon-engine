#include "Aeon/Aeon.h"
#include "Aeon/Streams/FileStream.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

FileStream::FileStream(const std::string &path, int access_mode /*= AccessMode::READ*/)
:
Stream(access_mode),
m_file(NULL)
{
	m_name = path;

	if(access_mode == (AccessMode::READ | AccessMode::WRITE))
	{
		Console::error("FileStream: Invalid access mode: Read+Write on file %s.", m_name.c_str());
		return;
	}

	__open_file();
}

FileStream::~FileStream()
{
}

void FileStream::__open_file()
{
	if (m_access_mode == AccessMode::READ)
		m_file = fopen(m_name.c_str(), "rb");
	else
		m_file = fopen(m_name.c_str(), "wb");

	if (!m_file)
	{
		Console::error("FileStream: Could not open file: %s", m_name.c_str());
		return;
	}

	if(m_access_mode == AccessMode::READ)
		__calculate_file_size();
}

void FileStream::__calculate_file_size()
{
	if (!m_file)
	{
		Console::error("FileStream: Size requested on unopened file.");
		return;
	}

	if (!seek(0, SeekDirection::End))
		Console::error("Could not determine file size for file: %s. Seek end failed.", m_name.c_str());

	m_size = ftell(m_file);

	if (m_size == 0)
		Console::warning("FileStream: File is empty: %s", m_name.c_str());

	if (!seek(0, SeekDirection::Begin))
		Console::error("Could not determine file size for file: %s. Seek begin failed.", m_name.c_str());
}

size_t FileStream::read(void *buffer, size_t count)
{
	if(!m_file)
	{
		Console::error("FileStream: Read on unopened file.");
		return 0;
	}

	if(m_access_mode != AccessMode::READ)
	{
		Console::error("FileStream: Can not read from file in write mode for file %s.", m_name.c_str());
		return 0;
	}

	if (!buffer)
	{
		Console::error("FileStream: Input buffer is NULL.");
		return 0;
	}

	if (count == 0)
	{
		Console::warning("FileStream: Tried writing 0 bytes.");
		return 0;
	}

	return fread(buffer, 1, count, m_file);
}

size_t FileStream::read_line(std::string &str)
{
	if (!m_file)
	{
		Console::error("FileStream: Read on unopened file.");
		return 0;
	}

	if (m_access_mode != AccessMode::READ)
	{
		Console::error("FileStream: Can not read from file in write mode for file %s.", m_name.c_str());
		return 0;
	}

	//AEON_FILE_LINE_BUFFER_SIZE
	std::string line;

	for (int i = 0; i < AEON_STREAM_MAX_TEXT_LINE_LENGTH; ++i)
	{
		int c = fgetc(m_file);

		if(c == EOF)
			break;

		if(c == '\n')
			break;

		line += (char) c;
	}

	str = line;

	return line.length();
}

size_t FileStream::write(const void *buffer, size_t count)
{
	if (!m_file)
	{
		Console::error("FileStream: Write on unopened file.");
		return 0;
	}

	if (m_access_mode != AccessMode::WRITE)
	{
		Console::error("FileStream: Can not write to file in read mode for file %s.", m_name.c_str());
		return 0;
	}

	if (!buffer)
	{
		Console::error("FileStream: Input buffer is NULL.");
		return 0;
	}

	if (count == 0)
	{
		Console::warning("FileStream: Tried writing 0 bytes.");
		return 0;
	}

	return fwrite(buffer, 1, count, m_file);
}

bool FileStream::seek(size_t pos, SeekDirection direction)
{
	if(!m_file)
	{
		Console::error("FileStream: Seek on unopened file.");
		return false;
	}

	switch (direction)
	{
		case SeekDirection::Begin:
		{
			return fseek(m_file, pos, SEEK_SET) == 0;
		}break;
		case SeekDirection::Current:
		{
			return fseek(m_file, pos, SEEK_CUR) == 0;
		}break;
		case SeekDirection::End:
		{
			return fseek(m_file, pos, SEEK_END) == 0;
		}break;
	};

	return false;
}

size_t FileStream::tell() const
{
	if(!m_file)
	{
		Console::error("FileStream: Tell on unopened file.");
		return 0;
	}

	return ftell(m_file);
}

bool FileStream::eof() const
{
	if (!m_file)
	{
		Console::error("FileStream: EOF on unopened file.");
		return true;
	}

	return (feof(m_file) != 0);
}

void FileStream::close()
{
	if (!m_file)
	{
		Console::error("FileStream: Close on unopened file.");
		return;
	}

	fclose(m_file);
	m_file = NULL;
}

void FileStream::flush()
{
	if (!m_file)
	{
		Console::error("FileStream: Close on unopened file.");
		return;
	}

	fflush(m_file);
}

bool FileStream::good()
{
	return m_file != NULL;
}

} //namespace Aeon
