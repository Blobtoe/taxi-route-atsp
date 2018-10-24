#include "adjacency_matrix.hpp"
#include "path.hpp"

#include <vector>

namespace tsp{
    class brute_force{

    public:
        brute_force() = delete;
        ~brute_force() = delete;

        static Path run(Adjacency_Matrix& matrix);

    private:
        static Adjacency_Matrix mat_;

        static void init_perms(std::vector<int>& perms);
        static void get_permutations(std::vector<int>& permutations, int begin, int end, Path& p);
        static void if_better_path(std::vector<int>& perms, Path& p);
        static int brute_force::get_cost(std::vector<int>& perms);


    };
}