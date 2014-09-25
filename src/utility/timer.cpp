#include "Aeon/Aeon.h"
#include "Aeon/Utility/Timer.h"

namespace aeon
{

timer::timer()
{
	reset();
}

timer::~timer()
{

}

void timer::reset()
{
	start_time_ = std::chrono::system_clock::now();
}

double timer::get_time_difference()
{
	std::chrono::time_point<std::chrono::system_clock> now = 
		std::chrono::system_clock::now();
	
    std::chrono::duration<double> elapsed_seconds = now - start_time_;

	return elapsed_seconds.count();
}

} /* namespace Aeon */
