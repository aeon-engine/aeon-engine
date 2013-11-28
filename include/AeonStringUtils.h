#ifndef AeonStringUtils_h__
#define AeonStringUtils_h__

namespace Aeon
{
namespace StringUtils
{

typedef std::vector<std::string> Strings;

/************************************************************************/
/* To strings                                                           */
/************************************************************************/

std::string int_to_string(int val, int length = 0);
std::string int64_to_string(long long val, int length = 0);
std::string int_to_hex_string(int val, int length = 0);
std::string bool_to_string(bool val);

/************************************************************************/
/* From strings                                                         */
/************************************************************************/

unsigned int string_to_int(std::string str);
bool string_to_bool(std::string str);

/************************************************************************/
/* String splitting                                                     */
/************************************************************************/

enum class SplitMode
{
	All,
	SkipEmpty
};

Strings &split(const std::string &s, char delim, Strings &elems, SplitMode mode = SplitMode::SkipEmpty);
Strings split(const std::string &s, char delim, SplitMode mode = SplitMode::SkipEmpty);

} //namespace StringUtils
} //namespace Aeon

#endif // AeonStringUtils_h__
