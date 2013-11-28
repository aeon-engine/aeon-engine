#ifndef AeonConfigFile_h__
#define AeonConfigFile_h__

namespace Aeon
{

class ConfigFile
{
public:
	ConfigFile(const char *path);
	~ConfigFile();

	/*!
	* Check if an entry is in the config file. This could be used to first-time
	* configuration checks.
	* \return True if the entry is found.
	*/
	bool						has_entry(std::string key);

	/*!
	* Get a string value. Returns default if the entry could not be found.
	*/
	std::string					get_string(std::string key, std::string defaultstr);

	/*!
	* Get an integer value. Returns default if the entry could not be found or
	* if the entry could not be converted to an integer.
	*/
	int							get_integer(std::string key, int defaultstr);

	/*!
	* Get a boolean value. Returns default if the entry could not ne found or
	* if the entry could not be converted to a boolean.
	*/
	bool						get_boolean(std::string key, bool defaultstr);

	/*!
	* Change/Add a config value. If the key exists, it will be overwritten.
	*/
	void						set_string(std::string key, std::string value);

	/*!
	* Change/Add a config value. If the key exists, it will be overwritten.
	*/
	void						set_integer(std::string key, int value);

	/*!
	* Change/Add a config value. If the key exists, it will be overwritten.
	*/
	void						set_boolean(std::string key, bool value);

	/*!
	* Create or update config file. The path given at the constructor is used. If the file did not exist,
	* it will be created.
	*/
	void						write();

private:
	std::string					m_path;
};

} //namespace Aeon

#endif // AeonConfigFile_h__
