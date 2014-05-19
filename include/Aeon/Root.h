#ifndef AeonRoot_h__
#define AeonRoot_h__

#include "Aeon/Utility/Singleton.h"
#include "Aeon/FrameListener.h"
#include "Aeon/Platforms/BasePlatform.h"

#ifdef AEON_USE_GLFW_PLATFORM
#  include "Aeon/Platforms/GLFWPlatform.h"
#endif

namespace Aeon
{

typedef std::list<FrameListener *> FrameListeners;

class Root : public Singleton<Root>
{
public:
	~Root();

	static bool						initialize(Platforms::BasePlatformPtr platform);

	void							run();
	void							stop();

	void							add_frame_listener(FrameListener *listener);
	void							remove_frame_listener(FrameListener *listener);
	void							remove_all_frame_listeners();

protected:
	Root(Platforms::BasePlatformPtr platform);

	bool							__initialize_impl(Platforms::BasePlatformPtr platform);

	bool							initialized_;
	bool							running_;

	FrameListeners					frame_listeners_;
	Platforms::BasePlatformPtr		platform_;
};

} /* namespace Aeon */

#endif /* AeonRoot_h__ */
