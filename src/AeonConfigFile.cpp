#include "Aeon.h"
#include "AeonConfigFile.h"

namespace Aeon
{

ConfigFile::ConfigFile(const char *path)
:
m_path(path)
{

}

ConfigFile::~ConfigFile()
{

}

bool ConfigFile::has_entry(std::string key)
{
	return false;
}

std::string ConfigFile::get_string(std::string key, std::string defaultstr)
{
	return "";
}

int ConfigFile::get_integer(std::string key, int defaultstr)
{
	return 0;
}

bool ConfigFile::get_boolean(std::string key, bool defaultstr)
{
	return true;
}

void ConfigFile::set_string(std::string key, std::string value)
{

}

void ConfigFile::set_integer(std::string key, int value)
{

}

void ConfigFile::set_boolean(std::string key, bool value)
{

}

void ConfigFile::write()
{

}

} //namespace Aeon
