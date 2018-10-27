#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>

class Adjacency_Matrix{

friend class File_Handler;
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

    bool load_from_file(std::fstream& file);
    std::vector<int> parse_file_input(std::string& line);

    void pretty_string(std::string& str_matrix) const;
    // Returns the amount of spaces needed to justify the matrix.
    int get_spaces(const int number) const;
};