#include "../include/adjacency_matrix.hpp"
#include <string>
#include <iostream>

void eksdi()
{
}

int main()
{
	Adjacency_Matrix a_m("../data/example.txt");
	std::cout << a_m.to_string();
}