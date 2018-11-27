#pragma once

#include "../include/adjacency_matrix.hpp"
#include "../include/path.hpp"

#include <string>
#include <vector>

class ATSP{

public:
    ATSP() = delete;
    ATSP(int nodes);
    ATSP(const std::vector<std::vector<int>>& matrix);
    ATSP(const std::string& filepath);
    ATSP(const ATSP&) = default;
    ATSP& operator=(const ATSP&) = default;
    ~ATSP() = default;
 
    Path brute_force();
    Path branch_n_bound_best();
    Path branch_n_bound_depth();
    Path held_karp();

private:
    Adjacency_Matrix matrix_;
};