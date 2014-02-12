#ifndef AeonGame_h__
#define AeonGame_h__

#include "AeonGameState.h"

namespace Aeon
{

class BaseApplication;

class Game
{
//TODO: Find a better way for this..
friend class BaseApplication;
friend class GLFWApplication;
public:
	Game();
	virtual ~Game();

	void					initialize();

	BaseApplication *		get_application() { return m_application; }

	void					set_gamestate(GameStatePtr gamestate);

protected:
	virtual bool			on_initialize() = 0;
	virtual void			on_run() = 0;
	virtual void			on_stop() = 0;
	virtual void			on_cleanup() = 0;

private:
	void					__register_application(BaseApplication *application);

	bool					on_update(float dt);
	void					on_render();

	BaseApplication *		m_application;
	GameStatePtr			m_current_gamestate;
};

typedef std::shared_ptr<Game> GamePtr;

} //namespace Aeon

#endif // AeonGame_h__
