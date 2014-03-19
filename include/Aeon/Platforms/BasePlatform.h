#ifndef BasePlatform_h__
#define BasePlatform_h__

#include "Aeon/Game.h"

namespace Aeon
{
namespace Platforms
{

class BasePlatform
{
public:
	BasePlatform() {}
	virtual ~BasePlatform() {}

	virtual void		run() = 0;
	virtual void		stop() = 0;
};

} /* namespace Platforms */
} /* namespace Aeon */

#endif // BasePlatform_h__
