#include "../include/city.hpp"

namespace tsp{

    City::City(const int index, const std::vector<std::vector<int>>& matrix, const int travel_cost = 0)
        : index_{ index }, reduction_matrix_{ matrix }, 
        previous_path_{ Path() }, 
        lower_bound_{ travel_cost }
    {
        reduction_matrix_.reduce_matrix();
        lower_bound_ = reduction_matrix_.get_reduction_cost();
        add_to_path(index, 0);
    }

    City::City(const City& city, const int index, const int travel_cost)
        : index_{ index },
        reduction_matrix_{ city.reduction_matrix_ }, 
        previous_path_{ city.previous_path_ }, 
        lower_bound_{ city.lower_bound_ + travel_cost }
    {
        reduce_matrix();
        add_to_path(index, travel_cost);
    }

    int City::get_bound() const
    {
        return lower_bound_;
    }

    int City::get_path_size() const
    {
        return previous_path_.path_.size();
    }

    int City::get_index() const
    {
        return index_;
    }

    Path City::get_path() const
    {
        return previous_path_;
    }

    int City::get_travel_cost(int source, int dest) const
    {
        return reduction_matrix_[source][dest];
    }

    std::vector<int> City::get_neighbours() const
    {
        return reduction_matrix_.get_neighbours(index_);
    }

    void City::reduce_matrix()
    {
        reduction_matrix_.fill_passed_nodes(
            previous_path_.get_prev_city(), index_);

        reduction_matrix_.reduce_matrix();
        lower_bound_ += reduction_matrix_.get_reduction_cost();
    }

    void City::add_to_path(const int index, const int cost)
    {
        previous_path_.add_to_path(index, cost);
    }
}