#include "Aeon.h"
#include "AeonConfigFile.h"
#include "AeonConsole.h"
#include "AeonStringUtils.h"
#include "AeonFileStream.h"

namespace Aeon
{

bool ConfigFile::has_entry(std::string key)
{
	auto itr = m_entries.find(key);

	return (itr != m_entries.end());
}

std::string ConfigFile::get_string(std::string key, std::string default_val)
{
	auto itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
	{
		set_string(key, default_val);
		return default_val;
	}

	return itr->second;
}

int ConfigFile::get_integer(std::string key, int default_val)
{
	auto itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
	{
		set_integer(key, default_val);
		return default_val;
	}

	int val = StringUtils::string_to_int(itr->second);
	return val;
}

bool ConfigFile::get_boolean(std::string key, bool default_val)
{
	auto itr = m_entries.find(key);

	//If it could not find the key...
	if (itr == m_entries.end())
	{
		set_boolean(key, default_val);
		return default_val;
	}

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

bool ConfigFile::load(const std::string &path)
{
	Console::debug("Reading config file: %s", path.c_str());

	FileStream file(path, Stream::AccessMode::READ);

	if (!file.good())
	{
		Console::warning("Could not load config file: %s", path.c_str());
		m_path = path;
		return false;
	}

	m_entries.clear();

	//Loop through all lines
	int linenumber = 0;
	while(!file.eof())
	{
		linenumber++;

		std::string line;
		if(file.read(line) == 0)
			continue;

		if(line.empty())
			continue;

		//Ignore comments and empty lines (these should only have a \n)
		if (line[0] == '#' || line[0] == '\n')
			continue;

		size_t pos = line.find_first_of('=');

		if (pos == std::string::npos || pos == 0)
		{
			Console::warning("Ignoring invalid line in config file %s line %u.", path.c_str(), linenumber);
			continue;
		}

		std::string key = line.substr(0, pos);
		std::string val = line.substr(pos+1);

		m_entries[key] = val;
	}

	file.close();

	Console::debug("Finished reading config file: %s", path.c_str());

	return true;
}

void ConfigFile::save()
{
	FileStream file(m_path, Stream::AccessMode::WRITE);

	if(!file.good())
	{
		Console::error("Could not save config file: %s", m_path.c_str());
		return;
	}

	//Loop through all entries to save to file
	for(auto itr = m_entries.begin(); itr != m_entries.end(); ++itr)
	{
		std::string line = itr->first + "=" + itr->second + "\n";
		file.write(line);
	}

	file.close();
}

} //namespace Aeon
