#include "Aeon/Aeon.h"
#include "Aeon/Utility/Timer.h"

namespace Aeon
{

Timer::Timer()
{
	reset();
}

Timer::~Timer()
{

}

void Timer::reset()
{
	start_time_ = std::chrono::system_clock::now();
}

double Timer::get_time_difference()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = now - start_time_;

	return elapsed_seconds.count();
}

} /* namespace Aeon */
