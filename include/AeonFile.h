#ifndef AeonFile_h__
#define AeonFile_h__

namespace Aeon
{
namespace File
{

enum class SeekDirection
{
	Begin,
	Current,
	End
};

enum class Mode
{
	Text,
	Binary
};

} //namespace File
} //namespace Aeon

#endif // AeonFile_h__
