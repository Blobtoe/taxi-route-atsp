#pragma once

#include "path.hpp"
#include "city.hpp"
#include "adjacency_matrix.hpp"
#include "bnb_containers.hpp"

#include <queue>
#include <functional>
#include <stack>
#include <memory>

namespace tsp{
    class branch_n_bound{

    using city_p_queue = std::priority_queue< City, std::vector<City>, City::compare>;

    public:
		branch_n_bound() = delete;
		branch_n_bound(const Adjacency_Matrix& matrix);

        Path dfs();
        Path best_fs();

    private:
        Adjacency_Matrix matrix_;
        int best_bound_;

        void init_matrix();

        Path run(std::shared_ptr<Container> container, Path& best_path);
        void handle_city(City& city, std::shared_ptr<Container> container, Path& best_path);
        void push_child_cities(City& parent_city, std::shared_ptr<Container> container);
        void update_best_bound(City& city, Path& best_path);
        void finalize_path(Path& best_path);
        void calc_travel_cost(Path& path); 
    };
}
