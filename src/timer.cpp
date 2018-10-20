#include "timer.hpp"

Timer::Timer(void (*fnc_to_measure)())
    : fnc_to_measure_{ fnc_to_measure }
{};

double Timer::run()
{
    start_counter();
    fnc_to_measure_();
    return get_time();
}

double Timer::run_average(const int executions)
{
    double accu_time{0};

    for(int i{0}; i < executions; ++i)
        accu_time += run();
    
    return accu_time/executions;
}

#ifdef __linux__

void Timer::start_counter()
{
    clock_gettime(CLOCK_REALTIME, &start_time_);
}

double Timer::get_time()
{
    struct timespec end_time_;
    clock_gettime(CLOCK_REALTIME, &end_time_);
    return ((end_time_.tv_sec - start_time_.tv_sec) +
            (end_time_.tv_nsec - start_time_.tv_nsec))/ 1000000000L;
}

#elif _WIN32
void Timer::start_counter()
{
    LARGE_INTEGER per_f;
    if(QueryPerformanceFrequency(&per_f))

    pc_freq_ = double(per_f.QuadPart)/1000.0;

    QueryPerformanceCounter(&per_f);
    start_time_ = per_f.QuadPart;
}

double Timer::get_time()
{
    LARGE_INTEGER per_f;
    QueryPerformanceCounter(&per_f);
    return double(per_f.QuadPart - start_time_)/pc_freq_;
}
#endif