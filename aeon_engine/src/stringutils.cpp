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
namespace string_utils
{

/************************************************************************/
/* To strings                                                           */
/************************************************************************/
std::string int_to_string(int val, int length /* = 0 */)
{
    if (length == 0)
    {
        return std::to_string(val);
    }

    std::stringstream stream;
    stream << std::setw(length) << std::setfill('0') << val;
    return stream.str();
}

std::string int_to_hex_string(int val, int length /* = 0 */)
{
    std::stringstream stream;

    if (length == 0)
    {
        stream << std::hex << val;
    }
    else
    {
        stream << std::hex << std::setw(length) << std::setfill('0') << val;
    }

    return stream.str();
}

std::string bool_to_string(bool val)
{
    return val == true ? "true" : "false";
}

std::string float_to_string(float val, int precision /* = 0 */)
{
    if (precision == 0)
    {
        return std::to_string(val);
    }

    std::stringstream stream;
    stream.setf(std::ios::fixed);
    stream << std::setw(precision) << val;
    return stream.str();  
}

std::string vector4f_to_string(glm::fvec4 val)
{
    std::string vector_str;
    vector_str += string_utils::float_to_string(val.x);
    vector_str += ' ';
    vector_str += string_utils::float_to_string(val.y);
    vector_str += ' ';
    vector_str += string_utils::float_to_string(val.z);
    vector_str += ' ';
    vector_str += string_utils::float_to_string(val.w);

    return vector_str;
}

/************************************************************************/
/* From strings                                                         */
/************************************************************************/
int string_to_int(const std::string &str)
{
    return std::stoi(str);
}

unsigned long string_to_uint(const std::string &str)
{
    return std::stoul(str);
}

float string_to_float(const std::string &str)
{
    return std::stof(str);
}

bool string_to_bool(const std::string &str)
{
    if (str == "true" || str == "1")
        return true;

    return false;
}

glm::fvec4 string_to_vector4f(const std::string &str)
{
    strings elements = split(str, ' ');

    float vec[4] = {1.0};

    for (std::size_t i = 0; i < 4; ++i)
    {
        if (elements.size() >= i + 1)
            vec[i] = string_to_float(elements[i]);
    }

    return glm::fvec4(vec[0], vec[1], vec[2], vec[3]);
}

/************************************************************************/
/* String splitting                                                     */
/************************************************************************/
strings &split(const std::string &s, char delim, strings &elems, 
               splitmode mode /* = SplitMode::SkipEmpty */)
{
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        // Do we need to skip empty items?
        if (mode == splitmode::skip_empty && item == "")
            continue;

        elems.push_back(item);
    }

    return elems;
}

strings split(const std::string &s, char delim, 
              splitmode mode /* = SplitMode::SkipEmpty */)
{
    strings elems;
    split(s, delim, elems, mode);
    return elems;
}

} // namespace string_utils
} // namespace aeon
