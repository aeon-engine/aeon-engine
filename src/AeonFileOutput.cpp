#include "Aeon.h"
#include "AeonFileOutput.h"
#include "AeonConsole.h"

namespace Aeon
{
namespace File
{

Output::Output()
:
m_file(NULL)
{

}

Output::~Output()
{
	close();
}

bool Output::open(const std::string &path)
{
	return open(path.c_str());
}

bool Output::open(const char *path)
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

void Output::close()
{
	if (m_file)
		fclose(m_file);

	m_file = NULL;
}

void Output::write(const std::string &path)
{
	write(path.c_str());
}

void Output::write(const char *text)
{
	if (!m_file || !text)
	{
		Console::error("Could not write to file.");
	}

	fputs(text, m_file);

	//Force write the text right now. This ensures the last info is logged even after a crash.
	fflush(m_file);
}

} //namespace File
} //namespace Aeon
