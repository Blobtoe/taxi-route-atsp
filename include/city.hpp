#pragma once

#include "path.hpp"

#include <vector>

namespace tsp{
    class City{

    public:

        City() = delete;
        City(const int index, const std::vector<std::vector<int>> matrix, const Path path, const int travel_cost);
        City(const City& city, const int index, const int travel_cost);
        ~City() = default;

        // bool operator==(const City& rhs);
        // bool operator!=(const City& rhs);

        bool operator<(const City& rhs);
        bool operator>(const City& rhs);

    private:

        int index_;
        int lower_bound_;
        std::vector<std::vector<int>> cost_matrix_;
        Path previous_path_;

        void reduce_matrix();
        void add_to_path(const int index, const int travel_cost);
    };
}