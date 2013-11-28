#ifndef AeonBaseApplication_h__
#define AeonBaseApplication_h__

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

protected:
	virtual bool		__initialize() = 0;
	virtual void		__cleanup() = 0;

	virtual void		__run() = 0;
	virtual void		__stop() = 0;

	Game *				m_game;
	bool				m_initialized;
};

} //namespace Aeon

#endif // AeonBaseApplication_h__
