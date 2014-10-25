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

#include "stdafx.h"

namespace aeon
{

bool configfile::has_entry(const std::string &key)
{
    auto itr = entries_.find(key);

    return (itr != entries_.end());
}

std::string configfile::get_string(const std::string &key, 
                                   const std::string &default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_string(key, default_val);
        return default_val;
    }

    return itr->second;
}

int configfile::get_integer(const std::string &key, int default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_integer(key, default_val);
        return default_val;
    }

    return string_utils::string_to_int(itr->second);
}

float configfile::get_float(const std::string &key, float default_val)
{
    auto itr = entries_.find(key);

    if (itr == entries_.end())
    {
        set_float(key, default_val);
        return default_val;
    }

    return string_utils::string_to_float(itr->second);
}

bool configfile::get_boolean(const std::string &key, bool default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_boolean(key, default_val);
        return default_val;
    }

    return string_utils::string_to_bool(itr->second);
}

glm::fvec4 configfile::get_vector4f(const std::string &key,
                                    glm::fvec4 default_val)
{
    auto itr = entries_.find(key);

    if (itr == entries_.end())
    {
        set_vector4f(key, default_val);
        return default_val;
    }

    return string_utils::string_to_vector4f(itr->second);
}

void configfile::set_string(const std::string &key, const std::string &val)
{
    entries_[key] = val;
}

void configfile::set_integer(const std::string &key, int val)
{
    set_string(key, string_utils::int_to_string(val));
}

void configfile::set_float(const std::string &key, float val)
{
    set_string(key, string_utils::float_to_string(val));
}

void configfile::set_boolean(const std::string &key, bool val)
{
    set_string(key, val ? "1" : "0");
}

void configfile::set_vector4f(const std::string &key, glm::fvec4 val)
{
    set_string(key, string_utils::vector4f_to_string(val));
}

bool configfile::load(stream_ptr stream)
{
    if (!stream->good())
    {
        console::warning("[ConfigFile]: Could not load config file: %s",
            stream->get_name().c_str());
        return false;
    }
    
    console::debug("[ConfigFile]: Reading config file: %s",
        stream->get_name().c_str());

    entries_.clear();

    // Loop through all lines
    int linenumber = 0;
    std::string header_name = "";
    while (!stream->eof())
    {
        linenumber++;

        std::string line;
        if (stream->read_line(line) == 0)
            continue;

        if (line.empty())
            continue;

        size_t length = line.size();

        // Ignore comments
        if (line[0] == '#')
            continue;

        // Is it a header?
        if (line[0] == '[')
        {
            // Then it should end with a ']'
            if (line[length - 1] == ']')
            {
                header_name = line.substr(1, length - 2);
                continue;
            }
        }

        // A header name should have been set beyond this point.
        if (header_name == "")
        {
            console::warning("[ConfigFile]: Ignoring invalid line in config "
                "file %s line %u. No header was found.", 
                stream->get_name().c_str(), linenumber);
            continue;
        }

        size_t pos = line.find_first_of('=');

        if (pos == std::string::npos || pos == 0)
        {
            console::warning("[ConfigFile]: Ignoring invalid line in config "
                "file %s line %u.", stream->get_name().c_str(), linenumber);
            continue;
        }

        std::string key = header_name + "." + line.substr(0, pos);
        std::string val = line.substr(pos + 1);

        entries_[key] = val;
    }

    console::debug("[ConfigFile]: Finished reading config file: %s",
        stream->get_name().c_str());

    stream->close();

    return true;
}

void configfile::save(stream_ptr stream)
{
    if (!stream->good())
    {
        console::error("[ConfigFile]: Could not save config file: %s",
            stream->get_name().c_str());
        return;
    }

    // Loop through all entries to save to file
    std::string header_name = "";
    for (auto itr : entries_)
    {
        string_utils::strings key = string_utils::split(
            itr.first, '.', string_utils::splitmode::skip_empty);

        // Do we have a new header name?
        if (key[0] != header_name)
        {
            header_name = key[0];
            stream->write("[" + header_name + "]\n");
        }

        std::string line = key[1] + "=" + itr.second + "\n";
        stream->write(line);
    }

    console::debug("[ConfigFile]: Finished saving config file: %s", 
        stream->get_name().c_str());

    stream->close();
}

} /* namespace aeon */
