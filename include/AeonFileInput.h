#ifndef AeonFileInput_h__
#define AeonFileInput_h__

namespace Aeon
{

//TODO: For now only binary files. Support text and binary in a neat interface.
class FileInput
{
public:
	enum class SeekDirection
	{
		Begin,
		Current,
		End
	};

	FileInput();
	~FileInput();

	bool				open(const std::string &path);
	bool				open(const char *path);
	void				close();

	size_t				read(unsigned char *buffer);
	size_t				read(unsigned char *buffer, size_t size);
	size_t				read(std::string &string);

	bool				seek(size_t count, SeekDirection direction);

	size_t				size()				{ return m_file_size; }

	FILE *				get_descriptor()	{ return m_file; }

private:
	FILE *				m_file;
	size_t				m_file_size;
};

} //namespace Aeon

#endif // AeonFileInput_h__
