#include "../include/menu_handler.hpp"
#include <string>

int main()
{
    std::string subtitles [4]{ "one", "two", "three", "fourfivesix"};
    Menu m{ Menu() };
    m.run(subtitles, 4, "MY MENU");
    return 0;
}