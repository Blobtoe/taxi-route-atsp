#pragma once

#include "path.hpp"
#include "reduction_matrix.hpp"

#include <vector>
#include <algorithm>

namespace tsp{
    class City{

    public:

        City() = default;
        City(const int index, const std::vector<std::vector<int>>& matrix, const int travel_cost);
        City(const City& city, const int index, const int travel_cost);

        City(const City& city) = default;
        City& operator=(const City& rhs) = default;
        ~City() = default;

        int get_bound() const;
        int get_path_size() const;
        int get_index() const;
        Path get_path() const;
        int get_travel_cost(int source, int dest) const;
        std::vector<int> get_neighbours() const;

        struct compare{
            bool operator()(const City& lhs, const City& rhs)
            {
                return (lhs.lower_bound_ > rhs.lower_bound_);
            }
        };

    private:

        int index_;
        int lower_bound_;
        Reduction_Matrix reduction_matrix_;
        Path previous_path_;

        void reduce_matrix();
        void add_to_path(const int index, const int travel_cost);
    };
}