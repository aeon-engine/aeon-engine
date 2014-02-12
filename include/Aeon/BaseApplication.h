#ifndef AeonBaseApplication_h__
#define AeonBaseApplication_h__

#include "Aeon/Game.h"

namespace Aeon
{

class Game;
class BaseApplication
{
public:
	BaseApplication();
	virtual ~BaseApplication();

	bool				initialize(GamePtr game);
	void				cleanup();

	void				run();
	void				stop();

protected:
	virtual bool		__initialize() = 0;
	virtual void		__cleanup() = 0;

	virtual void		__run() = 0;
	virtual void		__stop() = 0;

	GamePtr 			m_game;
	bool				m_initialized;
};

} //namespace Aeon

#endif // AeonBaseApplication_h__
