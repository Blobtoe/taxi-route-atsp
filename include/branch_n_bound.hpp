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

        static Path bfs(const Adjacency_Matrix& matrix);
        static Path dfs(const Adjacency_Matrix& matrix);
    
    private:
        static Adjacency_Matrix matrix_;
        static int best_cost_;

        static void init_matrix();
        
        static Path bfs(city_p_queue& city_q);
        static void handle_city(City& city, branch_n_bound::city_p_queue& city_, Path& best_path);
        static void push_child_cities(City& parent_city, city_p_queue& city_q);
        static void update_cost(City& city, Path& best_path);
        static void finalize_path(Path& best_path);

        static Path dfs(std::stack<City>& city_s);
        static void push_child_cities(City& parent_city, std::stack<City>& city_s);
        static void calc_travel_cost(Path& path);
        static std::vector<int> get_neighbours(City& city);
        static void remove_passed_neighbours(std::vector<int>& neighbours, City& city);
    };
}
