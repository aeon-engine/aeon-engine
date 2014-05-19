#ifndef BasePlatform_h__
#define BasePlatform_h__

#include "Aeon/Game.h"

namespace Aeon
{

class Root;

namespace Platforms
{

class BasePlatform
{
friend class Root;
public:
	BasePlatform() {}
	virtual ~BasePlatform() {}

protected:
	virtual bool				initialize() = 0;

	virtual bool				pre_frame() = 0;
	virtual bool				post_frame() = 0;

	virtual bool				dispose() = 0;
};

typedef std::shared_ptr<BasePlatform> BasePlatformPtr;

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* BasePlatform_h__ */
