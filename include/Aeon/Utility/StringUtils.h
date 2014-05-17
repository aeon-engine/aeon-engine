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
std::string float_to_string(float val, int precision = 0);

/************************************************************************/
/* From strings                                                         */
/************************************************************************/

unsigned int string_to_int(const std::string &str);
bool string_to_bool(const std::string &str);

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

#endif /* AeonStringUtils_h__ */
