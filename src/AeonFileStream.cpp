#include "Aeon.h"
#include "AeonFileStream.h"
#include "AeonConsole.h"

namespace Aeon
{

FileStream::FileStream(const std::string &path, int access_mode /*= AccessMode::READ*/)
:
Stream(access_mode),
m_file(NULL)
{
	m_name = path;
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
	{
		m_size = __get_file_size();
	}
}

size_t FileStream::__get_file_size()
{
	m_size = ftell(m_file);

	if (m_size == 0)
	{
		Console::warning("FileStream: File is empty: %s", m_name.c_str());
	}

	if (!seek(0, SeekDirection::Begin))
	{
		Console::error("Could not determine file size for file: %s. Seek begin failed.", path);
		return 0;
	}
}

size_t FileStream::read(void *buffer, size_t count)
{

}

size_t FileStream::write(const void *buffer, size_t count)
{

}

bool FileStream::seek(size_t pos, SeekDirection direction)
{
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

}

bool FileStream::eof() const
{

}

void FileStream::close()
{

}

} //namespace Aeon
