#include "Aeon.h"
#include "AeonFileOutput.h"
#include "AeonConsole.h"

namespace Aeon
{

FileOutput::FileOutput()
:
m_file(NULL)
{

}

FileOutput::~FileOutput()
{
	close();
}

bool FileOutput::open(const char *path)
{
	Console::debug("Opening file: %s", path);

	//Open the file
	m_file = fopen(path, "a");

	if (!m_file)
	{
		//Console::Print(Console::Error, "Could not open or create file: %s", path);
		return false;
	}

	return true;
}

void FileOutput::close()
{
	if (m_file)
		fclose(m_file);

	m_file = NULL;
}

void FileOutput::write(const char *text)
{
	if (!m_file || !text)
	{
		Console::error("Could not write to file.");
	}

	fputs(text, m_file);

	//Force write the text right now. This ensures the last info is logged even after a crash.
	fflush(m_file);
}

} //namespace Aeon
