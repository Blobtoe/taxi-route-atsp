#include "../include/city.hpp"

namespace tsp{

    City::City(const int index, 
                const std::vector<std::vector<int>> matrix, 
                const Path path, 
                const int travel_cost = 0)
        : index_{ index }, cost_matrix_{ matrix }, previous_path_{ path }, lower_bound_{ travel_cost }
    {}

    City::City(const City& city, 
                const int index, 
                const int travel_cost)
        : index_{ index }, 
            cost_matrix_{ city.cost_matrix_ }, 
            previous_path_{ city.previous_path_ }, 
            lower_bound_{ city.lower_bound_ + travel_cost }
    {

        add_to_path(index, travel_cost);

        // - reduce the matrix
        // - update the lower bound with the cost reduction
    }

    bool City::operator<(const City& rhs)
    {
        if(lower_bound_ < rhs.lower_bound_)
            return true;
        return false;
    }

    bool City::operator>(const City& rhs)
    {
        return !((*this) < rhs); 
    }

    void City::reduce_matrix()
    {
        
    }

    void City::add_to_path(const int index, const int cost)
    {
        previous_path_.add_to_path(index, cost);
    }
}