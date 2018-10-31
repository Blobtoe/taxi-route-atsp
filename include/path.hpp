#include <vector>
#include <string>

class Path{

public:
    std::vector<int> path_;
    int cost_;

    Path();
    Path(std::vector<int> path, const int cost);
    ~Path() = default;

    void add_to_path(const int node, const int cost);
    std::string to_string();

private:

    void pretty_string(std::string& path, int line_len);
    std::string get_path_str();
    std::string get_cost_str();
};