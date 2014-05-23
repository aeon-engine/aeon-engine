#ifndef gamestate_h__
#define gamestate_h__

namespace aeon
{

class game_state
{
public:
	game_state() {}
	virtual ~game_state() {}

	virtual void			on_enter() = 0;
	virtual void			on_leave() = 0;
};

typedef std::shared_ptr<game_state> game_state_ptr;

} //namespace aeon

#endif // gamestate_h__
