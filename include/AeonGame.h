#ifndef AeonGame_h__
#define AeonGame_h__
namespace Aeon
{

	class BaseApplication;

class Game
{
//TODO: Find a better way for this..
friend class BaseApplication;
friend class GLFWApplication;
public:
	virtual ~Game();

	void initialize();

	BaseApplication & get_application() { return m_application; }

protected:
	virtual bool on_initialize() = 0;
	virtual void on_stop() = 0;
	virtual void on_cleanup() = 0;

	virtual bool on_update(float dt) = 0;
	virtual void on_render() = 0;

private:
	Game(BaseApplication &application);

	BaseApplication &m_application;
};

} //namespace Aeon

#endif // AeonGame_h__
