#ifndef AeonFrameListener_h__
#define AeonFrameListener_h__

namespace Aeon
{

class FrameListener
{
public:
	FrameListener() {}
	~FrameListener() {}

	virtual bool on_frame(float dt) = 0;
	virtual bool on_render() = 0;
};

} /* namespace Aeon */

#endif /* AeonFrameListener_h__ */
