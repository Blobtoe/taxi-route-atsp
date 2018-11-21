#pragma once

#include "path.hpp"
#include "city.hpp"
#include "adjacency_matrix.hpp"

#include <queue>
#include <functional>
#include <stack>

namespace tsp{
    class branch_n_bound{

    using city_p_queue = std::priority_queue< City, std::vector<City>, City::compare>;

    public:
		branch_n_bound() = delete;
		branch_n_bound(const Adjacency_Matrix& matrix);

        Path best_fs();
        Path dfs();
    
    private:
        Adjacency_Matrix matrix_;
        int best_bound_;

        void init_matrix();
        Path run_best_fs(city_p_queue& city_q);
        void handle_city(City& city, branch_n_bound::city_p_queue& city_, Path& best_path);
        void push_child_cities(City& parent_city, city_p_queue& city_q);
        void update_best_bound(City& city, Path& best_path);
        void finalize_path(Path& best_path);

        Path run_dfs(std::stack<City>& city_s);
        void push_child_cities(City& parent_city, std::stack<City>& city_s);
        void calc_travel_cost(Path& path);
    };
}
