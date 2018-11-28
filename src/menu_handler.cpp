#include "../include/menu_handler.hpp"
#include "../include/brute_force.hpp"
#include "../include/timer.hpp"
#include "../include/branch_n_bound.hpp"
#include "../include/held_karp.hpp"

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

	draw_title(title, line_len + format_chars);
	draw_body(subtitles, size, line_len);

	std::cout << std::string(line_len + format_chars, '-') << std::endl;
	std::cout << "\n Your choice >> ";
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
	unsigned max_len{0};
	for(size_t i{0}; i < size; ++i)
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
	for(size_t i{1}; i <= size; ++i)
		std::cout << align_line(subtitles[i-1], i, max_line);
}

std::string Menu::align_line(const std::string& line, const unsigned line_no, const unsigned max_len) const
{
	return std::string("| " + std::to_string(line_no) + ") " 
		+ line + std::string(max_len - line.size(), ' ') + " |\n");
}

void Menu::handle_input(const std::string subtitles[], size_t size, std::string title)
{
	int choice = 4;
	bool exit = false;
	while(!exit)
	{
		draw_menu(subtitles, size, title);
		std::cin >> choice;
		switch(choice)
		{
			case 1:
			{
				get_filename();
				break;
			}
			case 2:
			{
				int amount{ 0 };
				std::cout << " Enter the amount of nodes >> ";
				std::cin >> amount;
				matrix = Adjacency_Matrix(amount);
				data_loaded = true;
				break;
			}
			case 3:
			{
				if(data_loaded)
				{
					display_matrix();
					wait_for_reaction();
				}
				break;
			}
			case 4:
			{
				if(data_loaded)
					algorithm_menu();
				break;
			}
			default:
			{
				exit = true;
				break;
			}
		}
	}
}

void Menu::get_filename()
{
	std::string filename;
	std::cout << " Enter the path to a file >> ";
	std::cin >> filename;
	load_from_file(filename);
}

void Menu::display_matrix()
{
	clear_term();
	std::cout << matrix.to_string();
}

void Menu::load_from_file(std::string& filename)
{
	try{
		matrix = Adjacency_Matrix(filename);
		data_loaded = true;
	}
	catch(const std::invalid_argument&)
	{
		std::cout << "\n Error: Incorrect path to a file.";
		getchar();	// get rid of the trailing newline
		getchar();
		clear_term();
	}
}

void Menu::wait_for_reaction()
{
	getchar();
	getchar();
}

void Menu::algorithm_menu()
{
	clear_term();
	std::string subtitles[] = { "Brute Force", "Branch and Bound - Best First Search",
		"Branch and Bound - Depth First Search", "Dynamic Programming", "Run all" ,"Back" };
	int choice = 4;
	bool exit = false;
	double time{ 0.0 };
	while (!exit)
	{
		draw_menu(subtitles, 6, "Algorithms");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			display_matrix();
			auto brutef{ tsp::brute_force(matrix) };
			time = run_algo([&brutef](){
				return brutef.run();
			});
			std::cout << "  Time [ms] >> " << time << std::endl;
			wait_for_reaction();
			break;
		}
		case 2:
		{
			display_matrix();
			auto bnb{ tsp::branch_n_bound(matrix) };
			time = run_algo([&bnb](){
				return bnb.best_fs();
			});
			std::cout << "  Time [ms] >> " << time;
			wait_for_reaction();
			break;
		}
		case 3:
		{
			display_matrix();
			auto bnb{ tsp::branch_n_bound(matrix) };
			time = run_algo([&bnb](){
				return bnb.dfs(); 
			});
			std::cout << "  Time [ms] >> " << time;
			wait_for_reaction();
			break;
		}
		case 4:
		{
			display_matrix();
			auto hk{ tsp::held_karp(matrix) };
			time = run_algo([&hk](){
				return hk.run();
			});
			std::cout << "  Time [ms] >> " << time;
			wait_for_reaction();
			break;
		}
		case 5:
		{
			display_matrix();
			run_all_algos();
			wait_for_reaction();
			break;
		}
		default:
		{
			exit = true;
			break;
		}
		}
	}
}

double Menu::run_algo(std::function<Path()> fnc)
{
	auto t{ Timer<Path>(fnc) };
	double time{ t.run() };
	std::cout << t.get_output().to_string();
	return time;
}

void Menu::run_all_algos()
{
	auto bf{ tsp::brute_force(matrix) };
	auto bnb{ tsp::branch_n_bound(matrix) };
	auto hk{ tsp::held_karp(matrix) };
	
	double time{0.0};

	time = run_algo([&bf](){
		return bf.run();
	});
	std::cout << "  Time[ms] >> " << time << "\n\n";
	
	time = run_algo([&bnb](){
		return bnb.best_fs();
	});
	std::cout << "  Time[ms] >> " << time << "\n\n";
	
	time = run_algo([&bnb](){
		return bnb.dfs();
	});
	std::cout << "  Time[ms] >> " << time << "\n\n";
	
	time = run_algo([&hk](){
		return hk.run();
	});
	std::cout << "  Time[ms] >> " << time << "\n\n";
}