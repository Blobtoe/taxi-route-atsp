#include "../include/algorithm.hpp"
#include <iostream>
#include <climits>

Path Algorithm::run(const int perm)
{
    int* input = new int[perm];
    for(int i{0}; i < perm; ++i)
    {
        input[i] = i;
    }
    Path p{ Path(INT_MAX) };
    bf(input, 0, perm, p);
}

void Algorithm::bf(int* arr, const int begin, const int end, Path& p)
{  
    if (begin == end)
        better_path(arr, end, p);
    else
    { 
        for (int i{ begin }; i <= end; i++) 
        { 
            std::swap(arr[begin], arr[i]); 
            bf(arr, begin+1, end, p); 
            std::swap(arr[begin], arr[i]);
        } 
    } 
}

void Algorithm::better_path(int* arr, int size, Path& current_best)
{
    int cost{ get_cost(arr, size) };
    if(cost < current_best.get_cost() )
        current_best = Path(arr, size, cost);
}

int Algorithm::get_cost(const int* arr, const int size) const
{
    int acc_cost{0};

    for(int i{0}; i + 1 < size; ++i)
        acc_cost += matrix_[arr[i]][arr[i + 1]];
    
    return acc_cost;
}

