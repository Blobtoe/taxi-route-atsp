#include "../include/adjacency_matrix.hpp"
#include "../include/brute_force.hpp"
#include "../include/timer.hpp"
#include "../include/timer.hpp"

#include "../include/menu_handler.hpp"

#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

int main()
{

    Adjacency_Matrix m{ Adjacency_Matrix("../data/test.txt") };
    std::cout << tsp::brute_force::run(m).to_string();
	
	auto t{ Timer<Path, Adjacency_Matrix&>(tsp::brute_force::run) };
	std::cout << "\n\n Time: " << t.run(m);
	//Menu m{ Menu() };

	system("pause");
}