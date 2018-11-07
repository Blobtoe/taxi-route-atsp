#include "../include/branch_n_bound.hpp"
#include <iostream>

namespace tsp{

    Adjacency_Matrix branch_n_bound::matrix_ = Adjacency_Matrix();
    int branch_n_bound::upper_bound_ = INT_MAX;

    Path branch_n_bound::bfs(const Adjacency_Matrix& matrix)
    {
        matrix_ = matrix;
        upper_bound_ = INT_MAX;
        init_matrix();
        auto city_q{ city_p_queue() };
        city_q.push(City(0, branch_n_bound::matrix_.data(), 0));
        return bfs(city_q);
    }

    void branch_n_bound::init_matrix()
    {
        for(int i{0}; i < matrix_.size(); ++i)
            matrix_[i][i] = INT_MAX;
    }

    Path branch_n_bound::bfs(branch_n_bound::city_p_queue& city_q)
    {
        Path best_path;
        while(!city_q.empty())
        {
            City current_city{ city_q.top() };
            city_q.pop();
            handle_city(current_city, city_q, best_path);
        }
        finalize_path(best_path);
        return best_path;
    }

    void branch_n_bound::handle_city(City& city, branch_n_bound::city_p_queue& city_q, Path& best_path)
    {
        if(city.get_path_size() == matrix_.size())
            update_upper_bound(city, best_path);
        else if(city.get_bound() < upper_bound_)  
            push_child_cities(city, city_q);
    }

    void branch_n_bound::update_upper_bound(City& city, Path& best_path)
    {
        if(city.get_bound() < upper_bound_)
        {
            upper_bound_ = city.get_bound();
            best_path = city.get_path();
        }
    }

    void branch_n_bound::push_child_cities(City& parent_city, branch_n_bound::city_p_queue& city_q)
    {
        int parent_index{ parent_city.get_index() }, travel_cost;
        std::vector<int> neighbours{ parent_city.get_neighbours() };

        for(auto& neighbour: neighbours)
        {
            travel_cost = parent_city.get_travel_cost(parent_index, neighbour);
            city_q.push(
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
        for(int i{0}; i < path.path_.size() - 1; ++i)
            travel_c += matrix_[path.path_[i]][path.path_[i+1]];
            
        path.cost_ = travel_c;
    }

    Path branch_n_bound::dfs(const Adjacency_Matrix& matrix)
    {
        branch_n_bound::matrix_ = matrix;
        branch_n_bound::upper_bound_ = INT_MAX;
        init_matrix();
        auto city_s{ std::stack<City>() };
        city_s.push(City(0, branch_n_bound::matrix_.data(), 0));
        return dfs(city_s);
    }

    Path branch_n_bound::dfs(std::stack<City>& city_s)
    {
        Path best_path;
        while(!city_s.empty())
        {
            City current_city{ city_s.top() };
            city_s.pop();

            if(current_city.get_path_size() == matrix_.size())
                update_upper_bound(current_city, best_path);
            else if(current_city.get_bound() <= upper_bound_)
                push_child_cities(current_city, city_s);
        }
        finalize_path(best_path);
        return best_path;
    }

    void branch_n_bound::push_child_cities(City& parent_city, std::stack<City>& city_s)
    {
        int parent_index{ parent_city.get_index() }, travel_cost;
        std::vector<int> neighbours{ parent_city.get_neighbours() };

        for(auto& neighbour: neighbours)
        {
            travel_cost = parent_city.get_travel_cost(parent_index, neighbour);
            city_s.push(
                City(parent_city, neighbour, travel_cost));
        }
    }
}