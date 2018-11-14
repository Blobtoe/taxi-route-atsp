#include "..\include\held_karp.hpp"
#include <iostream>

// Maska może przyjąć "(1 << matrix.size()) - 1 " wartości.
// Drugi element w std::pair<int, int> jest indeksem miasta,
// do którego weszła funkcja zwracająca minimalny koszt.

tsp::held_karp::held_karp(const Adjacency_Matrix& matrix)
	:	matrix_{ matrix }, 
		full_mask_{ (1 << matrix.size())  - 1 }
{
	operations_.resize(matrix_.size(), std::vector<int>( (1 << matrix_.size()) - 1 , INT_MAX ));
	travel_vec_.resize(matrix_.size(), std::vector<int>((1 << matrix_.size()) - 1, INT_MAX));
}

Path tsp::held_karp::run()
{
	init_matrix();
	int cost{ h_k(1, 0) };
	return get_path(cost);
}

// Zablokowanie możliwości stworzenia pętli w wyniku.
void tsp::held_karp::init_matrix()
{
	for (int i{ 0 }; i < matrix_.size(); ++i)
		matrix_[i][i] = INT_MAX;
}

// Główna rekurencja działająca według wzoru:
// - C(S, i) = min {C(S - {j}, i) + d(j, i)}, gdzie:
//		- d(j, i) - Dystans między wierzchołkami (j, i) w grafie.
//		- C(S, i) - Koszt przejścia cyklu hamiltona od i przez wszystkie wierzchołki w S.
int tsp::held_karp::h_k(visited_mask mask, int city)
{
	if (mask == full_mask_)
		return matrix_[city][0];
		
	if (operations_[city][mask.mask_] != INT_MAX)
		return operations_[city][mask.mask_];

	int current{ INT_MAX };
	for (int i{0}; i < matrix_.size(); ++i)
	{
		auto i_mask{ visited_mask::int_to_mask(i) };
		if (visited_mask::and_masks(mask, i_mask) == 0)
		{
			current = h_k(visited_mask::sum_masks(mask, i_mask), i) + matrix_[city][i];

			if (current < operations_[city][mask.mask_])
			{
				operations_[city][mask.mask_] = current;
				travel_vec_[city][mask.mask_] = i;
			}			
		}
	}
	return operations_[city][mask.mask_];
}

// Przejście po kolejnych maskach w celu odtworzenia minimalnej ścieżki.
Path tsp::held_karp::get_path(int cost)
{
	std::vector<int> path = { 0 };
	visited_mask i_mask{ visited_mask::int_to_mask(0) };
	int index{ 0 };

	while(i_mask != full_mask_)
	{
		index = travel_vec_[index][i_mask.mask_];
		path.push_back(index);
		i_mask = visited_mask::sum_masks(i_mask, visited_mask::int_to_mask(index));
	}
	path.push_back(0);
	return Path(path, cost, "DP");
}

