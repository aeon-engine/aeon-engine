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
unsigned int string_to_int(std::string str)
{
	std::stringstream myString(str);
	int val = 0;
	myString >> val;

	return val;
}

/************************************************************************/
/* String splitting                                                     */
/************************************************************************/
Strings &split(const std::string &s, char delim, Strings &elems, bool checkEmpty /* = true */)
{
	std::stringstream ss(s);
	std::string item;

	while (std::getline(ss, item, delim))
	{
		//Do we need to skip empty items?
		if (checkEmpty && item == "")
			continue;

		elems.push_back(item);
	}

	return elems;
}

Strings split(const std::string &s, char delim, bool checkEmpty /* = true */)
{
	Strings elems;
	split(s, delim, elems, checkEmpty);
	return elems;
}

} //namespace StringUtils
} //namespace Aeon
