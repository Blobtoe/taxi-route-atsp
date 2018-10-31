#pragma once

#include "adjacency_matrix.hpp"
#include "path.hpp"

#include <vector>

namespace tsp{
    class brute_force{

    public:
        brute_force() = delete;

        static Path run(Adjacency_Matrix& matrix);

    private:
        static Adjacency_Matrix mat_;

        static void init_perms(std::vector<int>& perms);
        static void permutate(std::vector<int>& permutations, const int begin, const int end, Path& p);
        static void update_if_better(std::vector<int>& perms, Path& p);
        static int get_cost(const std::vector<int>& perms);
		static void add_last_path(Path& p);
    };
}