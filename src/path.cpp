#include "../include/path.hpp"

Path::Path(std::vector<int> path, const int cost)
    : path_{ path }, cost_{ cost }
{}

std::string Path::to_string()
{
    auto output{ std::string() };
    for(auto& p: path_)
        output += std::to_string(p) + " ";
    output += "\n" + std::to_string(cost_);
    return output;
}
