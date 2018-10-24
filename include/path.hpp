#include <vector>
#include <string>

class Path{

public:
    Path(std::vector<int> path, const int cost);
    ~Path() = default;

    std::vector<int> path_;
    int cost_;

    std::string to_string();
};