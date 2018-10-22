#ifdef __linux__
#include <time.h>
#elif _WIN32
#include <Windows.h>
#endif

template<typename T, typename ... Args>
class Timer{

public:
    Timer() = delete;
	
	Timer(T(*fnc_to_measure)(Args ... args))
		: fnc_to_measure_{ fnc_to_measure }
	{};

    ~Timer() = default;
    Timer& operator=(const Timer& rhs) = default;

	T get_ret_copy();

    double run(Args ... args);
    double run_average(const int executions);

private:

    T (*fnc_to_measure_)(Args ... args);
	T ret_copy_;

    void start_counter();
    double get_time();

	// Attributes for OS specific timing functions.
    #ifdef __linux__
    struct timespec start_time_;

    #elif _WIN32
    double pc_freq_ = 0.0;
    long long start_time_;
    
    #endif
};

template<typename T, typename ... Args>
T Timer<T, Args ...>::get_ret_copy()
{
	return ret_copy_;
}

template<typename T, typename ... Args>
double Timer<T, Args ... >::run(Args ... args)
{
	start_counter();
	ret_copy_ = fnc_to_measure_(args ...);
	return get_time();
}

template<typename T, typename ... Args>
double Timer<T, Args ...>::run_average(const int executions)
{
	double accu_time{ 0 };

	for (int i{ 0 }; i < executions; ++i)
		accu_time += run();

	return accu_time / executions;
}

#ifdef __linux__

template<typename T, typename ... Args>
void Timer<T, Args ...>::start_counter()
{
	clock_gettime(CLOCK_REALTIME, &start_time_);
}

template<typename T, typename ... Args>
double Timer<T, Args ...>::get_time()
{
	struct timespec end_time_;
	clock_gettime(CLOCK_REALTIME, &end_time_);
	return ((end_time_.tv_sec - start_time_.tv_sec) +
		(end_time_.tv_nsec - start_time_.tv_nsec)) / 1000000000L;
}

#elif _WIN32
template<typename T, typename ... Args>
void Timer<T, Args ...>::start_counter()
{
	LARGE_INTEGER per_f;
	if (QueryPerformanceFrequency(&per_f))

		pc_freq_ = double(per_f.QuadPart) / 1000.0;

	QueryPerformanceCounter(&per_f);
	start_time_ = per_f.QuadPart;
}

template<typename T, typename ... Args>
double Timer<T, Args ...>::get_time()
{
	LARGE_INTEGER per_f;
	QueryPerformanceCounter(&per_f);
	return double(per_f.QuadPart - start_time_) / pc_freq_;
}
#endif