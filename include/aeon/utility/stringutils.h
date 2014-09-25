#ifndef stringutils_h__
#define stringutils_h__

namespace aeon
{
namespace string_utils
{

typedef std::vector<std::string> strings;

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

enum class splitmode
{
	all,
	skip_empty
};

strings &split(const std::string &s, char delim, strings &elems, 
	splitmode mode = splitmode::skip_empty);
strings split(const std::string &s, char delim, 
	splitmode mode = splitmode::skip_empty);

} //namespace strin_utils
} //namespace aeon

#endif // stringutils_h__
