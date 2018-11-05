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
	Menu m{ Menu() };
	std::string subtitles[] = {"Wczytaj dane z pliku.", "Wyswietl aktualne dane.", "Uruchom algorytmy.", "Wyjscie"};
	m.run(subtitles, 4, "Menu");
	return 0;
}