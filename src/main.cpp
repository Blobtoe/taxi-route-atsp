#include "../include/adjacency_matrix.hpp"
#include "../include/menu_handler.hpp"
#include "../include/brute_force.hpp"

#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

int main()
{
    Adjacency_Matrix m{ Adjacency_Matrix("../data/example.txt") };
    std::cout << tsp::brute_force::run(m).to_string();
	system("pause");
}