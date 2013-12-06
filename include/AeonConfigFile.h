#ifndef AeonConfigFile_h__
#define AeonConfigFile_h__

#include "AeonStream.h"

namespace Aeon
{

class ConfigFile
{
public:
	/*!
	* Constructor
	*/
	ConfigFile() {}

	/*!
	 * Destructor
	 */
	~ConfigFile() {}

	/*!
	 * Check if the loaded config file has a certain entry key
	 * \param key The entry key to be checked
	 * \returns True if the entry was found
	 */
	bool						has_entry(const std::string &key);

	/*!
	 * Get a string value from the loaded config file.
	 * \param key The entry key
	 * \param default_val The default value to be used when the key was not found or was invalid.
	 * \returns The value or the default value
	 */
	std::string					get_string(const std::string &key, const std::string &default_val);

	/*!
	* Get an integer value from the loaded config file.
	* \param key The entry key
	* \param default_val The default value to be used when the key was not found or was invalid.
	* \returns The value or the default value
	*/
	int							get_integer(const std::string &key, int default_val);

	/*!
	* Get a boolean value from the loaded config file.
	* \param key The entry key
	* \param default_val The default value to be used when the key was not found or was invalid.
	* \returns The value or the default value
	*/
	bool						get_boolean(const std::string &key, bool default_val);

	/*!
	* Set a string value in the loaded config file.
	* \param key The entry key
	* \param val The value
	*/
	void						set_string(const std::string &key, const std::string &val);

	/*!
	* Set an integer value in the loaded config file.
	* \param key The entry key
	* \param val The value
	*/
	void						set_integer(const std::string &key, int val);

	/*!
	* Set a boolean value in the loaded config file.
	* \param key The entry key
	* \param val The value
	*/
	void						set_boolean(const std::string &key, bool val);

	/*!
	 * Load a config from a stream
	 * \param stream The stream to load the config from
	 * \returns True on success, false on error.
	 */
	bool						load(Stream &stream);

	/*!
	* Save a config to a stream
	* \param stream The stream to save the config to
	*/
	void						save(Stream &stream);

private:
	typedef std::map<std::string, std::string> Entries;

	Entries						m_entries;
};

} //namespace Aeon

#endif // AeonConfigFile_h__
