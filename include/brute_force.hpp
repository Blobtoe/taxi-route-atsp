#pragma once

#include "adjacency_matrix.hpp"
#include "path.hpp"

#include <vector>

namespace tsp{
    class brute_force{

    public:
		brute_force(Adjacency_Matrix& matrix);

		Path run();

    private:
        Adjacency_Matrix mat_;

        void init_perms(std::vector<int>& perms);
        void permutate(std::vector<int>& permutations, const int begin, const int end, Path& p);
        void update_if_better(std::vector<int>& perms, Path& p);
        int get_cost(const std::vector<int>& perms);
    };
}