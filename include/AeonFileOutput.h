#ifndef AeonFileOutput_h__
#define AeonFileOutput_h__

#include "AeonFile.h"

namespace Aeon
{
namespace File
{

//TODO: For now only text files. Support text and binary in a neat interface.
class Output
{
public:
	Output();
	~Output();

	bool				open(const std::string &path);
	bool				open(const char *path);
	void				close();

	void				write(const std::string &path);
	void				write(const char *text);


	FILE *				get_descriptor()	{ return m_file; }

	bool				opened()			{ return m_file != NULL; }

private:
	FILE *				m_file;
};

} //namespace File
} //namespace Aeon

#endif // AeonFileOutput_h__
