#ifdef __linux__
#include <time.h>
#elif _WIN32
#include <Windows.h>
#endif

class Timer{

public:
    Timer() = delete;
    Timer(void (*fnc_to_measure)());
    ~Timer() = default;
    Timer& operator=(const Timer& rhs) = default;

    double run();
    double run_average(const int executions);

private:
    void (*fnc_to_measure_)();

    void start_counter();
    double get_time();

    #ifdef __linux__
    struct timespec start_time_;

    #elif _WIN32
    double pc_freq_ = 0.0;
    long long start_time_;
    
    #endif

};