#include "aeon/aeon.h"
#include "aeon/utility/stringutils.h"

namespace aeon
{
namespace string_utils
{

/************************************************************************/
/* To strings                                                           */
/************************************************************************/
std::string int_to_string(int val, int length /* = 0 */)
{
    std::stringstream stream;

    if(length == 0)
    {
        stream << val;
    }else{
        stream << std::setw(length) << std::setfill('0') << val;
    }

    return stream.str();
}

std::string int64_to_string(long long val, int length /* = 0 */)
{
    std::stringstream stream;

    if(length == 0)
    {
        stream << val;
    }else{
        stream << std::setw(length) << std::setfill('0') << val;
    }

    return stream.str();
}

std::string int_to_hex_string(int val, int length /* = 0 */)
{
    std::stringstream stream;

    if(length == 0)
    {
        stream << val;
    }else{
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
    std::stringstream stream;
    stream.setf(std::ios::fixed);

    if(precision == 0)
    {
        stream << val;
    }else{
        stream << std::setw(precision) << val;
    }

    return stream.str();  
}

/************************************************************************/
/* From strings                                                         */
/************************************************************************/
unsigned int string_to_int(const std::string &str)
{
    std::stringstream myString(str);
    int val = 0;
    myString >> val;

    return val;
}

bool string_to_bool(const std::string &str)
{
    if(str == "true" || str == "1")
        return true;

    return false;
}

/************************************************************************/
/* String splitting                                                     */
/************************************************************************/
strings &split(const std::string &s, char delim, strings &elems, 
    splitmode mode /* = SplitMode::SkipEmpty */)
{
    std::stringstream ss(s);
    std::string item;

    while(std::getline(ss, item, delim))
    {
        //Do we need to skip empty items?
        if(mode == splitmode::skip_empty && item == "")
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

} /* namespace StringUtils */
} /* namespace Aeon */
