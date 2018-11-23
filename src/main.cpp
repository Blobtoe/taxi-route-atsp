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
	std::string subtitles[] = {"Load data from a file.", "Generate a random asymmetric graph.", "Display the current graph.", "Run the algorithms.", "Exit"};
	m.run(subtitles, 5, "Menu");
	return 0;
}