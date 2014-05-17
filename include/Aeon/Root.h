#ifndef AeonRoot_h__
#define AeonRoot_h__

#include "Aeon/Utility/Singleton.h"
#include "Aeon/FrameListener.h"

namespace Aeon
{

typedef std::list<FrameListener *> FrameListeners;

class Root : public Singleton<Root>
{
public:
	Root();
	~Root();

	void				render();
	void				stop();

	void				add_frame_listener(FrameListener *listener);
	void				remove_frame_listener(FrameListener *listener);
	void				remove_all_frame_listeners();

protected:
	void				__initialize();
	void				__cleanup();

	bool				initialized_;

	FrameListeners		frame_listeners_;
};

} /* namespace Aeon */

#endif /* AeonRoot_h__ */
