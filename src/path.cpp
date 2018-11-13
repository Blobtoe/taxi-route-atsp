#include "../include/path.hpp"
#include <iostream>

Path::Path()
    : path_{ std::vector<int>() }, cost_{0}
{}

Path::Path(std::vector<int> path, const int cost)
    : path_{ path }, cost_{ cost }
{}

void Path::add_to_path(const int node, const int cost)
{
    path_.push_back(node);
    cost_ += cost;
}

int Path::get_prev_city()
{
    return path_[path_.size() - 1];
}

std::string Path::to_string()
{
    std::string path{ get_path_str() };
    std::string cost{ get_cost_str() };
    std::string output{ "| Path >> " + path + " |\n"};

    size_t line_len{ output.size() };

    output += "| Cost >> " + cost;
    pretty_string(output, line_len);
    return output;
}

void Path::pretty_string(std::string& path, int line_len)
{
    size_t cost_str_len{ path.size() - line_len};
    size_t spaces{line_len - cost_str_len - 2};
    
    path.append(std::string(spaces, ' '));  
    path.append("|\n");
    std::string dashes{ std::string(line_len - 1, '-') + "\n"};
    path.insert(0, dashes);
    path.append(dashes);
}

std::string Path::get_path_str()
{
    auto output{ std::string() };
    for(size_t i{0}; i < path_.size(); ++i)
    {
        output += std::to_string(path_[i]);
        if(i < path_.size() - 1)
            output += "->";
    }
    return output;
}

std::string Path::get_cost_str()
{
    return std::to_string(cost_);
}
