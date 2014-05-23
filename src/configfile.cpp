#include "Aeon/Aeon.h"
#include "Aeon/ConfigFile.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Utility/StringUtils.h"
#include "Aeon/Streams/FileStream.h"

namespace Aeon
{

bool ConfigFile::has_entry(const std::string &key)
{
	auto itr = entries_.find(key);

	return (itr != entries_.end());
}

std::string ConfigFile::get_string(const std::string &key, const std::string &default_val)
{
	auto itr = entries_.find(key);

	//If it could not find the key...
	if(itr == entries_.end())
	{
		set_string(key, default_val);
		return default_val;
	}

	return itr->second;
}

int ConfigFile::get_integer(const std::string &key, int default_val)
{
	auto itr = entries_.find(key);

	//If it could not find the key...
	if(itr == entries_.end())
	{
		set_integer(key, default_val);
		return default_val;
	}

	int val = StringUtils::string_to_int(itr->second);
	return val;
}

bool ConfigFile::get_boolean(const std::string &key, bool default_val)
{
	auto itr = entries_.find(key);

	//If it could not find the key...
	if(itr == entries_.end())
	{
		set_boolean(key, default_val);
		return default_val;
	}

	return StringUtils::string_to_bool(itr->second);
}

void ConfigFile::set_string(const std::string &key, const std::string &val)
{
	entries_[key] = val;
}

void ConfigFile::set_integer(const std::string &key, int val)
{
	set_string(key, StringUtils::int_to_string(val));
}

void ConfigFile::set_boolean(const std::string &key, bool val)
{
	set_string(key, val ? "1" : "0");
}

bool ConfigFile::load(StreamPtr stream)
{
	if(!stream->good())
	{
		Console::warning("Could not load config file: %s", stream->get_name().c_str());
		return false;
	}
	
	Console::debug("Reading config file: %s", stream->get_name().c_str());

	entries_.clear();

	//Loop through all lines
	int linenumber = 0;
	std::string header_name = "";
	while(!stream->eof())
	{
		linenumber++;

		std::string line;
		if(stream->read_line(line) == 0)
			continue;

		if(line.empty())
			continue;

		size_t length = line.size();

		//Ignore comments
		if(line[0] == '#')
			continue;

		//Is it a header?
		if(line[0] == '[')
		{
			//then it should end with a ']'
			if (line[length - 1] == ']')
			{
				header_name = line.substr(1, length - 2);
				continue;
			}
		}

		//A header name should have been set beyond this point.
		if(header_name == "")
		{
			Console::warning("Ignoring invalid line in config file %s line %u. No header was found.", stream->get_name().c_str(), linenumber);
			continue;
		}

		size_t pos = line.find_first_of('=');

		if(pos == std::string::npos || pos == 0)
		{
			Console::warning("Ignoring invalid line in config file %s line %u.", stream->get_name().c_str(), linenumber);
			continue;
		}

		std::string key = header_name + "." + line.substr(0, pos);
		std::string val = line.substr(pos + 1);

		entries_[key] = val;
	}

	Console::debug("Finished reading config file: %s", stream->get_name().c_str());

	stream->close();

	return true;
}

void ConfigFile::save(StreamPtr stream)
{
	if(!stream->good())
	{
		Console::error("Could not save config file: %s", stream->get_name().c_str());
		return;
	}

	//Loop through all entries to save to file
	std::string header_name = "";
	for(auto itr : entries_)
	{
		StringUtils::Strings key = StringUtils::split(itr.first, '.', StringUtils::SplitMode::SkipEmpty);

		//do we have a new header name?
		if(key[0] != header_name)
		{
			header_name = key[0];
			stream->write("[" + header_name + "]\n");
		}

		std::string line = key[1] + "=" + itr.second + "\n";
		stream->write(line);
	}

	Console::debug("Finished saving config file: %s", stream->get_name().c_str());

	stream->close();
}

} /* namespace Aeon */
