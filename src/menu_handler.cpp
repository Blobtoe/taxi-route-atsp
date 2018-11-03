#include "../include/menu_handler.hpp"
#include "../include/brute_force.hpp"
#include "../include/timer.hpp"
#include "../include/branch_n_bound.hpp"

#include <string>
#include <iostream>

void Menu::run(const std::string subtitles[], size_t size, const std::string title)
{
	handle_input(subtitles, size, title);
}

void Menu::draw_menu(const std::string subtitles[], size_t size, const std::string title) const
{
	clear_term();

	int line_len{ longest_subtitle(subtitles, size)};

	draw_title(title, line_len + 7);
	draw_body(subtitles, size, line_len);
	std::cout << std::string(line_len + extra_chars, '-') << std::endl;
	std::cout << "\n Twoj wybor >> ";
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
	unsigned dash_count{ line_len - (unsigned)title.size() - 2 };
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

void Menu::handle_input(const std::string subtitles[], size_t size, std::string title)
{
	int choice = 4;
	while(true)
	{
		draw_menu(subtitles, size, title);
		std::cin >> choice;
		switch(choice)
		{
			case 1:
			{
				std::string filename;
				std::cout << " Podaj nazwe pliku >> ";
				std::cin >> filename;
				load_from_file(filename);
				break;
			}
			case 2:
			{
				clear_term();
				if(data_loaded)
					std::cout << matrix.to_string();
				getchar();
				getchar();
				break;
			}
			case 3:	// Algorytmy
			{
				//auto t{Timer<Path, Adjacency_Matrix&>(tsp::brute_force::run)};
				//double time {t.run(matrix)};
				auto path{ tsp::branch_n_bound::bfs(matrix)};
				//clear_term();
				std::cout << matrix.to_string();
				//std::cout << t.get_output().to_string();
				std::cout << path.to_string();
				getchar();
				getchar();
				break;
			}
		}
	}
}

void Menu::load_from_file(std::string& filename)
{
	try{
		matrix = Adjacency_Matrix(filename);
		data_loaded = true;
	}
	catch(const std::invalid_argument&)
	{
		std::cout << "\n Podano nieprawidlowy plik.";
		getchar();	// get rid of the trailing newline
		getchar();
		clear_term();
	}
}
