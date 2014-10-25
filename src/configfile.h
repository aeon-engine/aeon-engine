/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#ifndef configfile_h__
#define configfile_h__

namespace aeon
{

/*!
 * \brief Reader and writer for files in .ini file format
 *
 * Allows reading and writing configuration settings to a stream. Usually this
 * means a config ini file. If the config file contains syntax errors, messages
 * are logged to the console.
 */
class configfile
{
public:
    /*!
    * Constructor
    */
    configfile() {}

    /*!
     * Destructor
     */
    ~configfile() {}

    /*!
     * Check if the loaded config file has a certain entry key
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    bool has_entry(const std::string &key);

    /*!
     * Get a string value from the loaded config file.
     * \param key The entry key
     * \param default_val The default value to be used when the key 
     *                    was not found or was invalid.
     * \returns The value or the default value
     */
    std::string get_string(const std::string &key, 
                           const std::string &default_val);

    /*!
    * Get an integer value from the loaded config file.
    * \param key The entry key
    * \param default_val The default value to be used when the key 
    *                    was not found or was invalid.
    * \returns The value or the default value
    */
    int get_integer(const std::string &key, int default_val);

    float get_float(const std::string &key, float default_val);

    /*!
    * Get a boolean value from the loaded config file.
    * \param key The entry key
    * \param default_val The default value to be used when the key
    *                    was not found or was invalid.
    * \returns The value or the default value
    */
    bool get_boolean(const std::string &key, bool default_val);

    
    glm::fvec4 get_vector4f(const std::string &key, glm::fvec4 default_val);

    /*!
    * Set a string value in the loaded config file.
    * \param key The entry key. Must be in the format "header.keyname".
    * \param val The value
    */
    void set_string(const std::string &key, const std::string &val);

    /*!
    * Set an integer value in the loaded config file.
    * \param key The entry key. Must be in the format "header.keyname".
    * \param val The value
    */
    void set_integer(const std::string &key, int val);

    void set_float(const std::string &key, float val);

    /*!
    * Set a boolean value in the loaded config file.
    * \param key The entry key. Must be in the format "header.keyname".
    * \param val The value
    */
    void set_boolean(const std::string &key, bool val);
    
    void set_vector4f(const std::string &key, glm::fvec4 val);

    /*!
     * Load a config from a stream
     * \param stream The stream to load the config from
     * \returns True on success, false on error.
     */
    bool load(stream_ptr stream);

    /*!
    * Save a config to a stream
    * \param stream The stream to save the config to
    */
    void save(stream_ptr stream);

private:
    typedef std::map<std::string, std::string> Entries;

    Entries entries_;
};

} /* namespace aeon */

#endif /* configfile_h__ */
