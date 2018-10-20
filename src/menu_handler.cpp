#include "../include/menu_handler.hpp"

#include <string>
#include <iostream>

Menu::Menu(bool (*file_fnc)(std::fstream&))
	: file_fnc_{ file_fnc }
{}

void Menu::run(const std::string subtitles[], size_t size, const std::string title)
{
	draw_menu(subtitles, size, title);
}

void Menu::draw_menu(const std::string subtitles[], size_t size, const std::string title) const
{
	clear_term();

	int line_len{ longest_subtitle(subtitles, size)};

	draw_title(title, line_len + 7);
	draw_body(subtitles, size, line_len);
	std::cout << std::string(line_len + extra_chars, '-') << std::endl;
}

void Menu::clear_term() const
{
	#ifdef __linux__
	system("clear");
	#elif _WIN32
	system("CLS");
	#endif
}

int Menu::longest_subtitle(const std::string subtitles[], size_t size) const
{
	int max_len{0};
	for(int i{0}; i < size; ++i)
	{
		if(max_len < subtitles[i].size())
			max_len = subtitles[i].size();
	}
	return max_len;
}

void Menu::draw_title(const std::string& title, const unsigned line_len) const
{
	unsigned int dash_count{ line_len - (unsigned)title.size() - 2 };
	auto dashes{ std::string((int) dash_count/2, '-') };
	auto title_string{ std::string( dashes + " " + title + " " + dashes) };

	if(dash_count % 2 == 0)
		std::cout <<  title_string << std::endl;
	else
		std::cout << title_string << "-" << std::endl;

}

void Menu::draw_body(const std::string subtitles[], size_t size, const unsigned max_line) const
{
	for(int i{1}; i <= size; ++i)
		std::cout << add_extra_chars(subtitles[i-1], i, max_line);
}

// Adds extra characters and empty spaces to align the last vertical line.
std::string Menu::add_extra_chars(const std::string& line, const unsigned line_no, const unsigned max_len) const
{
	return std::string("| " + std::to_string(line_no) + ") " 
		+ line + std::string(max_len - line.size(), ' ') + " |\n");
}

