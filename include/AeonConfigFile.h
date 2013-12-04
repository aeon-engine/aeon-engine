#ifndef AeonConfigFile_h__
#define AeonConfigFile_h__

#include "AeonStream.h"

namespace Aeon
{

class ConfigFile
{
public:
	ConfigFile() {}
	~ConfigFile() {}

	bool						has_entry(std::string key);

	std::string					get_string(std::string key, std::string default_val);
	int							get_integer(std::string key, int default_val);
	bool						get_boolean(std::string key, bool default_val);

	void						set_string(std::string key, std::string val);
	void						set_integer(std::string key, int val);
	void						set_boolean(std::string key, bool val);

	bool						load(Stream &stream);
	void						save(Stream &stream);

private:
	typedef std::map<std::string, std::string> Entries;

	Entries						m_entries;
};

} //namespace Aeon

#endif // AeonConfigFile_h__
