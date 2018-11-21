#include "../include/adjacency_matrix.hpp"
#include "../include/brute_force.hpp"
#include "../include/timer.hpp"
#include "../include/timer.hpp"
#include "../include/menu_handler.hpp"

#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <time.h>
int main()
{
	srand(time(NULL));
	Menu m{ Menu() };
	std::string subtitles[] = {"Wczytaj dane z pliku.", "Wygeneruj losowy graf", "Wyswietl aktualne dane.", "Uruchom algorytmy.","Pomiary", "Wyjscie"};
	m.run(subtitles, 6, "Menu");
	return 0;
}