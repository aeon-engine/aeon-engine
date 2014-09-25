#ifndef timer_h__
#define timer_h__

#include <ctime>
#include <chrono>

namespace aeon
{

class timer
{
public:
    timer();
    ~timer();

    void reset();

    double get_time_difference();

private:
    std::chrono::time_point<std::chrono::system_clock> start_time_;
};

} //namespace aeon

#endif // timer_h__
