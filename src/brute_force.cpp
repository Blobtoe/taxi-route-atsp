#include "../include/brute_force.hpp"
#include <climits>

namespace tsp{

	Adjacency_Matrix brute_force::mat_ = Adjacency_Matrix();

    Path brute_force::run(Adjacency_Matrix& matrix)
    {
        brute_force::mat_ = matrix;

        Path p{ Path(std::vector<int>(), INT_MAX) };
        std::vector<int> perms{ std::vector<int>(matrix.size()) };
        init_perms(perms);

        get_permutations(perms, 1, matrix.size() - 1, p);
        return p;
    }

    void brute_force::init_perms(std::vector<int>& perms)
    {
        for(int i{0}; i < perms.size(); ++i)
            perms[i] = i;
    }

    void brute_force::get_permutations(std::vector<int>& perms, int begin, int end, Path& p)
    {
        if (begin == end)
            if_better_path(perms, p);
        else
        { 
            for (int i{ begin }; i <= end; ++i) 
            { 
                std::swap(perms[begin], perms[i]); 
                get_permutations(perms, begin + 1, end, p); 
                std::swap(perms[begin], perms[i]);
            } 
        }
    }

    void brute_force::if_better_path(std::vector<int>& perms, Path& p)
    {
        int updated_cost{ get_cost(perms) };
        if(updated_cost < p.cost_)
        {
            p.path_ = perms;
            p.cost_ = updated_cost;
        }
    }

    int brute_force::get_cost(std::vector<int>& perms)
    {
        int acc_cost{0};

        for(int i{0}; i + 1 < perms.size(); ++i)
            acc_cost += mat_[perms[i]][perms[i + 1]];

        return acc_cost;
    }
}