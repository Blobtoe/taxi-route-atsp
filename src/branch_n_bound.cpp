#include "../include/branch_n_bound.hpp"
#include <iostream>

namespace tsp{

	branch_n_bound::branch_n_bound(const Adjacency_Matrix& matrix)
		: matrix_{ matrix }, best_bound_{ INT_MAX }
	{
		init_matrix();
	}

	void branch_n_bound::init_matrix()
	{
		for (int i{ 0 }; i < matrix_.size(); ++i)
			matrix_[i][i] = INT_MAX;
	}

    Path branch_n_bound::dfs()
    {
		best_bound_ = INT_MAX;
        std::shared_ptr<Container> container{ new Stack(std::stack<City>()) };
        container->push(City(0, branch_n_bound::matrix_.data(), 0));
        Path best_path;
        best_path.algo_name_ = "B&B - DFS";
        return run(container, best_path);
    }

    Path branch_n_bound::best_fs()
	{
		best_bound_ = INT_MAX;
        std::shared_ptr<Container> container{ new Priority_Queue(city_p_queue()) };
        container->push(City(0, branch_n_bound::matrix_.data(), 0));
        Path best_path;
        best_path.algo_name_ = "B&B - Best-FS";
        return run(container, best_path);
    }

    Path branch_n_bound::run(std::shared_ptr<Container> container, Path& best_path)
    {
		City current_city;
        while(!container->empty())
        {
            current_city = container->top();
            container->pop();
            handle_city(current_city, container, best_path);
        }
        finalize_path(best_path);
        return best_path;
    }
	
    void branch_n_bound::handle_city(City& city, std::shared_ptr<Container> container, Path& best_path)
    {
        if(city.get_path_size() == matrix_.size())
            update_best_bound(city, best_path);
        else if(city.get_bound() < best_bound_)  
            push_child_cities(city, container);
    }

    void branch_n_bound::update_best_bound(City& city, Path& best_path)
    {
        if(city.get_bound() < best_bound_)
        {
            std::string algo_name{ best_path.algo_name_ };
            best_bound_ = city.get_bound();
            best_path = city.get_path();
            best_path.algo_name_ = algo_name;
        }
    }

    void branch_n_bound::push_child_cities(City& parent_city, std::shared_ptr<Container> container)
    {
        int parent_index{ parent_city.get_index() }, travel_cost;
        std::vector<int> neighbours{ parent_city.get_neighbours() };

        for(auto& neighbour: neighbours)
        {
            travel_cost = parent_city.get_travel_cost(parent_index, neighbour);
            container->push(
                City(parent_city, neighbour, travel_cost));
        }
    }

    void branch_n_bound::finalize_path(Path& path)
    {
        path.path_.push_back(0);
        calc_travel_cost(path);
    }

    void branch_n_bound::calc_travel_cost(Path& path)
    {
        int travel_c{0};
        for(size_t i{0}; i < path.path_.size() - 1; ++i)
            travel_c += matrix_[path.path_[i]][path.path_[i+1]];
            
        path.cost_ = travel_c;
    }
}