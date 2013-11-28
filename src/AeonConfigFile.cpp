#include "Aeon.h"
#include "AeonConfigFile.h"
#include "AeonFileInput.h"
#include "AeonConsole.h"
#include "AeonStringUtils.h"

namespace Aeon
{

bool ConfigFile::has_entry(std::string key)
{
	Entries::iterator itr = m_entries.find(key);

	return (itr != m_entries.end());
}

std::string ConfigFile::get_string(std::string key, std::string default_val)
{
	Entries::iterator itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
		return default_val;

	return itr->second;
}

int ConfigFile::get_integer(std::string key, int default_val)
{
	Entries::iterator itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
		return default_val;

	int val = StringUtils::string_to_int(itr->second);
	return val;
}

bool ConfigFile::get_boolean(std::string key, bool default_val)
{
	Entries::iterator itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
		return default_val;

	return StringUtils::string_to_bool(itr->second);
}

void ConfigFile::set_string(std::string key, std::string val)
{
	m_entries[key] = val;
}

void ConfigFile::set_integer(std::string key, int val)
{
	set_string(key, StringUtils::int_to_string(val));
}

void ConfigFile::set_boolean(std::string key, bool val)
{
	set_string(key, val ? "1" : "0");
}

bool ConfigFile::load(const char *path)
{
	FileInput file;
	if (!file.open(path))
	{
		Console::warning("Could not load config file: %s", path);
		return false;
	}

	std::string data;
	file.read(data);

	bool result = __parse_config_file(data);

	file.close();

	return result;
}

void ConfigFile::save()
{

}

bool ConfigFile::__parse_config_file(std::string &data)
{
	m_entries.clear();
	StringUtils::Strings lines = StringUtils::split(data, '\n', StringUtils::SplitMode::SkipEmpty);

	//Loop through all lines
	for(StringUtils::Strings::iterator itr = lines.begin(); itr != lines.end(); ++itr)
	{
		std::string &line = *itr;

		//Ignore comments.
		if(line[0] == '#')
			continue;

		size_t pos = line.find_first_of('=');

		if(pos == std::string::npos || pos == 0)
		{
			Console::warning("Ignoring invalid line in config file: %s", line.c_str());
			continue;
		}

		std::string key = line.substr(0, pos);
		std::string val = line.substr(pos);

		m_entries[key] = val;
	}

	return true;
}

} //namespace Aeon
