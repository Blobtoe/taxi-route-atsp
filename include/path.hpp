#include <vector>
#include <string>

class Path{

public:
    Path(std::vector<int> path, const int cost);
    ~Path() = default;

    std::vector<int> path_;
    int cost_;

    std::string to_string();
    void pretty_string(std::string& path, int line_len);

    std::string get_path_str();
    std::string get_cost_str();
};