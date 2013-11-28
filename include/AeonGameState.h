#ifndef AeonGameState_h__
#define AeonGameState_h__

namespace Aeon
{

class GameState
{
public:
	GameState() {}
	virtual ~GameState() {}

	virtual void			on_enter() = 0;
	virtual void			on_leave() = 0;

	virtual bool			on_update(float dt) = 0;
	virtual void			on_render() = 0;
};

}

#endif // AeonGameState_h__
