/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace aeon
{
namespace utility
{

class configfile_exception : public std::exception
{
};

/*!
 * \brief Reader and writer for files in .ini file format
 *
 * Allows reading and writing configuration settings to a stream. Usually this
 * means a config ini file. If the config file contains syntax errors, messages
 * are logged to the console.
 */
class configfile : public utility::noncopyable
{
public:
    using entries = std::map<std::string, std::string>;

    /*!
     * Constructor
     */
    configfile() = default;

    /*!
     * Destructor
     */
    ~configfile() = default;

    configfile(configfile &&other) noexcept
        : entries_(std::move(other.entries_))
    {
    }

    configfile &operator=(configfile &&other) noexcept
    {
        entries_ = std::move(other.entries_);
        return *this;
    }

    /*!
     * Check if the loaded config file has a certain entry key
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    bool has_entry(const std::string &key);

    /*!
     * Get a value.
     * \param key The entry key
     * \return Either the value of the entry of key, or throws an exception.
     */
    template <typename T>
    auto get(const std::string &key)
    {
        auto itr = entries_.find(key);

        // If it could not find the key...
        if (itr == entries_.end())
            throw configfile_exception{};

        return string::convert<T>::from(itr->second);
    }

    /*!
     * Get a value.
     * \param key The entry key
     * \param default_val Default value. If the key is not found in the config file, the default value is returned.
     * \return Either the value of the entry of key, or the default value.
     */
    template <typename T>
    auto get(const std::string &key, const T &default_val)
    {
        auto itr = entries_.find(key);

        // If it could not find the key...
        if (itr == entries_.end())
        {
            set<T>(key, default_val);
            return default_val;
        }

        return string::convert<T>::from(itr->second);
    }

    /*!
     * Set a value
     * \param key The entry key
     * \param val The value.
     */
    template <typename T>
    void set(const std::string &key, const T &val)
    {
        entries_[key] = string::convert<T>::to(val);
    }

    /*!
     * Load a config from a stream
     * \param stream The configfile to load
     */
    void load(streams::stream &stream);

    /*!
     * Save a config to a stream
     * \param stream The configfile to save.
     */
    void save(streams::stream &stream);

    /*!
     * Load a config from a file
     * \param path The configfile path to load
     */
    void load(const std::string &path);

    /*!
     * Save a config to a file
     * \param path The configfile path to save.
     *             File will be overwritten if it already exists.
     */
    void save(const std::string &path);

    /*!
     * Load a config from memory
     * \param data Vector to load from. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators. The vector must be moved
     *             into the config file due to the way the underlaying
     *             stream works.
     */
    void load(std::vector<std::uint8_t> &&data);

    /*!
     * Save a config to memory
     * \param data Vector to save to. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators. The vector will be
     *             cleared first.
     */
    void save(std::vector<std::uint8_t> &data);

    /*!
     * Begin iterator for foreach loops.
     */
    auto begin() const noexcept
    {
        return entries_.cbegin();
    }

    /*!
     * End iterator for foreach loops.
     */
    auto end() const noexcept
    {
        return entries_.cend();
    }

private:
    /*!
     * Handle a line when loading a file
     */
    void __read_line(const std::string &line);

    entries entries_;
};

} // namespace utility
} // namespace aeon
