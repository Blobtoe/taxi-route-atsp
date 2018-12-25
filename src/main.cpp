#include "../include/adjacency_matrix.hpp"
#include "../include/brute_force.hpp"
#include "../include/menu_handler.hpp"
#include "../include/timer.hpp"

#include <time.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>

int main()
{
    srand(time(NULL));
    Menu m{Menu()};
    std::string subtitles[] = {
        "Load data from a file.", "Generate a random asymmetric graph.",
        "Display the current graph.", "Run the algorithms.", "Exit"};
    m.run(subtitles, 5, "Menu");
    return 0;
}