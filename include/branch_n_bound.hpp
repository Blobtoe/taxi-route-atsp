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
        //static Path dfs(const Adjacency_Matrix& matrix);
    
    private:
        static Adjacency_Matrix matrix_;
        static int best_cost_;

        static void init_matrix();
        
        static Path bfs(city_p_queue& city_q);
        static void push_child_cities(City& parent_city, city_p_queue& city_q);
        static void update_cost(City& city, Path& best_path);
        //static Path dfs(std::stack<City>& city_s);
    };
}
