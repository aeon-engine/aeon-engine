#ifndef AeonBaseApplication_h__
#define AeonBaseApplication_h__

#include "AeonConsole.h"

namespace Aeon
{

class Game;
class BaseApplication
{
public:
	BaseApplication();
	virtual ~BaseApplication();

	bool				initialize(Game *game);
	void				cleanup();

	void				run();
	void				stop();

	Console &			get_console() { return m_console; }

protected:
	virtual bool		__initialize() = 0;
	virtual void		__cleanup() = 0;

	virtual void		__run() = 0;
	virtual void		__stop() = 0;

	Game *				m_game;
	bool				m_initialized;
	Console				m_console;
};

} //namespace Aeon

#endif // AeonBaseApplication_h__
