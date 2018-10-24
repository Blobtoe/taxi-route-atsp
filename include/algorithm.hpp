#include "adjacency_matrix.hpp"
#include "path.hpp"

class Algorithm{

public:
    Algorithm(const Adjacency_Matrix& matrix)
        : matrix_{ matrix }
    {};
    Path run(const int perm);
    void bf(int* arr, const int begin, const int end, Path& p);


protected:
    const Adjacency_Matrix& matrix_; 

    void better_path(int* arr, int size, Path& current_best);
    int get_cost(const int* arr, const int size) const;
};