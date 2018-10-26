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
	//Menu m{ Menu() };
	//std::string subtitles[] = {"Wczytaj dane z pliku.", "Wyswietl aktualne dane.", "Uruchom algorytmy."};
	//m.run(subtitles, 3, "Menu");
	Adjacency_Matrix a = Adjacency_Matrix("/home/desktop/Desktop/github/tsp/data/test.txt");
	auto t{ Timer<Path, Adjacency_Matrix&>(tsp::brute_force::run)};
	std::cout << t.run(a) << std::endl;
	std::cout << t.get_output().to_string();
}