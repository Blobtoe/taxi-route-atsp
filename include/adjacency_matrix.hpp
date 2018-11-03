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
    Adjacency_Matrix(const Adjacency_Matrix& rhs) = default;
    virtual ~Adjacency_Matrix() = default;

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    std::vector<int>& operator[](const int index);

    int size() const;
    std::string to_string() const;
    std::vector<std::vector<int>> data() const;

    virtual std::vector<int> get_neighbours(int node) const;

protected:

    std::vector<std::vector<int>> a_matrix_;

    void pretty_string(std::string& str_matrix) const;
    // Returns the amount of spaces needed to justify the matrix.
    int get_spaces(const int number) const;

private:

    bool load_from_file(std::fstream& file);
    std::vector<int> parse_file_input(std::string& line);
};