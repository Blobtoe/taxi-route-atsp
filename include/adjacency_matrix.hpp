#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

class Adjacency_Matrix{

public:
    Adjacency_Matrix();
    Adjacency_Matrix(std::vector<std::vector<int>> input);
    Adjacency_Matrix(const std::string& filename);

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    const std::vector<int>& operator[](const int index) const;

    int size() const;
    std::string to_string() const;

private:
    std::vector<std::vector<int>> a_matrix_;

    static bool load_from_file(std::fstream& file, Adjacency_Matrix& matrix);
    std::vector<int> parse_file_input(std::string& line);
};