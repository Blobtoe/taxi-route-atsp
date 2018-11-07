#pragma once

#include "adjacency_matrix.hpp"
#include <climits>

namespace tsp
{
    class Reduction_Matrix : public Adjacency_Matrix{

    public:
        Reduction_Matrix(Adjacency_Matrix matrix);
        Reduction_Matrix(std::vector<std::vector<int>> matrix);
        Reduction_Matrix(const Reduction_Matrix& r_m) = default;
        Reduction_Matrix& operator=(const Reduction_Matrix& rhs) = default;
        const std::vector<int>& operator[](int index) const;
        ~Reduction_Matrix() override = default;

        void fill_passed_nodes(int row, int column);
        void reduce_matrix();

        int get_reduction_cost() const;
        std::vector<int> get_neighbours(int node) const override;

    private:
        int reduction_cost_;
        
        void fill_row(int row);
        void fill_column(int column);

        int horizontal_reduction();
        int vertical_reduction();
        int get_row_min(const size_t row) const;
        int get_column_min(const size_t column) const;
    };
}