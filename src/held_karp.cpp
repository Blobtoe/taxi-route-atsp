#include "..\include\held_karp.hpp"
#include <iostream>


tsp::held_karp::held_karp(const Adjacency_Matrix& matrix)
	:	matrix_{ matrix }, 
		full_mask_{ pow(2, matrix_.size()) - 1 },
		saved_ops_{std::vector<std::vector<int>>( matrix_.size(), std::vector<int>((1 << matrix_.size()) - 1, INT_MAX)) }
{}

Path tsp::held_karp::run()
{
	init_matrix();
	std::cout << std::endl;
	std::cout << "Wynik " << h_k(1, 0) << std::endl;
	return Path();
}

void tsp::held_karp::init_matrix()
{
	for (int i{ 0 }; i < matrix_.size(); ++i)
		matrix_[i][i] = INT_MAX;
}

int tsp::held_karp::h_k(visited_mask mask, int city)
{
	if (mask == full_mask_)
	{
		std::cout << "Edge:" << mask.mask_ << std::endl;
		return matrix_[city][0];
	}
		

	if (saved_ops_[city][mask.mask_] != INT_MAX)
		return saved_ops_[city][mask.mask_];

	int current{ INT_MAX };
	for (int i{0}; i < matrix_.size(); ++i)
	{
		auto i_mask{ visited_mask::int_to_mask(i) };
		if (visited_mask::and_masks(mask, i_mask) == 0)
		{
			current = h_k(visited_mask::sum_masks(mask, i_mask), i) + matrix_[city][i];

			if (current < saved_ops_[city][mask.mask_])
				saved_ops_[city][mask.mask_] = current;	
		}
	}
	std::cout << "Edge:" << mask.mask_ << std::endl;
	return saved_ops_[city][mask.mask_];
}
