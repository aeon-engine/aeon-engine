#ifndef AeonTimer_h__
#define AeonTimer_h__

#include <ctime>
#include <chrono>

namespace Aeon
{

class Timer
{
public:
	Timer();
	~Timer();

	void													reset();

	double													get_time_difference();

private:
	std::chrono::time_point<std::chrono::system_clock>		start_time_;
};

} //namespace Aeon

#endif /* AeonTimer_h__ */
