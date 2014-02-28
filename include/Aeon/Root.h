#ifndef AeonRoot_h__
#define AeonRoot_h__

#include "Aeon/Utility/Singleton.h"

namespace Aeon
{

class Root : public Singleton<Root>
{
public:
	Root();
	~Root();

	bool				initialize();

	void				render();
	void				stop();

protected:
	bool				__initialize();
	void				__cleanup();

	bool				m_initialized;
};

} //namespace Aeon

#endif

