#ifndef AeonConfigFile_h__
#define AeonConfigFile_h__

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

	bool						load(const char *path);
	void						save();

private:
	bool						__parse_config_file(std::string &data);

	typedef std::map<std::string, std::string> Entries;

	std::string					m_path;
	Entries						m_entries;
};

} //namespace Aeon

#endif // AeonConfigFile_h__
