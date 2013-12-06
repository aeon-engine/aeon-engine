#include "Aeon.h"
#include "AeonStringUtils.h"

namespace Aeon
{
namespace StringUtils
{

/************************************************************************/
/* To strings                                                           */
/************************************************************************/
std::string int_to_string(int val, int length /* = 0 */)
{
	std::stringstream stream;

	if (length == 0)
	{
		stream << val;
	}
	else{
		stream << std::setw(length) << std::setfill('0') << val;
	}

	return stream.str();
}

std::string int64_to_string(long long val, int length /* = 0 */)
{
	std::stringstream stream;

	if (length == 0)
	{
		stream << val;
	}
	else{
		stream << std::setw(length) << std::setfill('0') << val;
	}

	return stream.str();
}

std::string int_to_hex_string(int val, int length /* = 0 */)
{
	std::stringstream stream;

	if (length == 0)
	{
		stream << val;
	}
	else{
		stream << std::hex << std::setw(length) << std::setfill('0') << val;
	}

	return stream.str();
}

std::string bool_to_string(bool val)
{
	return val == true ? "true" : "false";
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
Strings &split(const std::string &s, char delim, Strings &elems, SplitMode mode /* = SplitMode::SkipEmpty */)
{
	std::stringstream ss(s);
	std::string item;

	while (std::getline(ss, item, delim))
	{
		//Do we need to skip empty items?
		if (mode == SplitMode::SkipEmpty && item == "")
			continue;

		elems.push_back(item);
	}

	return elems;
}

Strings split(const std::string &s, char delim, SplitMode mode /* = SplitMode::SkipEmpty */)
{
	Strings elems;
	split(s, delim, elems, mode);
	return elems;
}

} //namespace StringUtils
} //namespace Aeon
