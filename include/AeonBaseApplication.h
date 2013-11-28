#ifndef AeonBaseApplication_h__
#define AeonBaseApplication_h__

namespace Aeon
{

class Game;
class BaseApplication
{
public:
	virtual ~BaseApplication();

	void				initialize();
	void				cleanup();

	void				run();
	void				stop();

protected:
	BaseApplication(Game &game);

	virtual void		__initialize() = 0;
	virtual void		__cleanup() = 0;

	virtual void		__run() = 0;
	virtual void		__stop() = 0;

	Game &				m_game;
};

} //namespace Aeon

#endif // AeonBaseApplication_h__
