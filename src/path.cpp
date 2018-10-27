#include "../include/path.hpp"
#include <iostream>

Path::Path(std::vector<int> path, const int cost)
    : path_{ path }, cost_{ cost }
{}

std::string Path::to_string()
{
    std::string path{ get_path_str() };
    std::string cost{ get_cost_str() };
    std::string output{ "| Path >> " + path + " |\n"};

    int line_len{ output.size() };

    output += "| Cost >> " + cost;
    pretty_string(output, line_len);
    return output;
}

void Path::pretty_string(std::string& path, int line_len)
{
    int cost_str_len{ path.size() - line_len};
    int spaces{line_len - cost_str_len - 2};
    
    // Justifies the last line and adds a vertical line to it.
    path.append(std::string(spaces, ' '));  
    path.append("|\n");
    std::string dashes{ std::string(line_len - 1, '-') + "\n"};
    path.insert(0, dashes);
    path.append(dashes);
}

std::string Path::get_path_str()
{
    auto output{ std::string() };
    for(int i{0}; i < path_.size(); ++i)
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
