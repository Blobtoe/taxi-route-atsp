#include "../include/brute_force.hpp"
#include <climits>

namespace tsp{

	brute_force::brute_force(Adjacency_Matrix& matrix)
		: mat_{ matrix }
	{}

    Path brute_force::run()
    {
        Path p{ Path(std::vector<int>(), INT_MAX) };
        std::vector<int> perms{ std::vector<int>(mat_.size() + 1) };
        init_perms(perms);

        permutate(perms, 1, mat_.size() - 1, p);
        return p;
    }

    void brute_force::init_perms(std::vector<int>& perms)
    {
        for(int i{0}; i < (int)perms.size() - 1; ++i)
            perms[i] = i;
		perms[perms.size() - 1] = 0;
    }

	// Permutuje indeksy w wektorze.
	// Po uzyskaniu jednej pełnej permutacji sprawdza, czy ta ścieżka jest lepsza od aktualnej najlepszej.
    void brute_force::permutate(std::vector<int>& perms, int begin, int end, Path& p)
    {
		if (begin == end)
			update_if_better(perms, p);
        else
        { 
            for (int i{ begin }; i <= end; ++i) 
            { 
                std::swap(perms[begin], perms[i]); 
                permutate(perms, begin + 1, end, p); 
                std::swap(perms[begin], perms[i]);
            } 
        }
    }

    void brute_force::update_if_better(std::vector<int>& perms, Path& p)
    {
        int updated_cost{ get_cost(perms) };
        if(updated_cost < p.cost_)
        {
            p.path_ = perms;
            p.cost_ = updated_cost;
        }
    }

	// Zwraca koszt przejścia przez miasta o indeksach zawartych w "perms".
    int brute_force::get_cost(const std::vector<int>& perms)
    {
        int acc_cost{0};
		for (size_t i{ 0 }; i + 1 < perms.size(); ++i)
			acc_cost += mat_[perms[i]][perms[i + 1]];

        return acc_cost;
    }
}