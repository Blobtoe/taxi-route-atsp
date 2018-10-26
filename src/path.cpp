#include "../include/path.hpp"

Path::Path(std::vector<int> path, const int cost)
    : path_{ path }, cost_{ cost }
{}

std::string Path::to_string()
{
    auto output{ std::string() };
    for(int i{0}; i < path_.size(); ++i)
    {
        output += std::to_string(path_[i]);
        if(i < path_.size() - 1)
            output += "->";
    }
    pretty_string(output);
    return output;
}

void Path::pretty_string(std::string& path)
{
    const unsigned special_chars{ 9 }; // "Path >> " + space at the end
    unsigned dash_count{ (unsigned)path.size() + special_chars};
    std::string dashes{ std::string("-", dash_count)};
    dashes += "\n";
    path.insert(0, "| Path >> ");
    path.insert(path.size(), " |\n");
    //path.insert(0, dashes);
    //path.append(dashes);
}
