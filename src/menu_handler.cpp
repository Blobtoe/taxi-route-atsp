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
				std::cout << " Podaj ilosc wierzcholkow >> ";
				std::cin >> amount;
				matrix = Adjacency_Matrix(generate_random(amount));
				data_loaded = true;
				break;
			}
			case 3:
			{
				if(data_loaded)
					display_matrix();
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
	std::cout << " Podaj nazwe pliku >> ";
	std::cin >> filename;
	load_from_file(filename);
}

void Menu::display_matrix()
{
	clear_term();
	if(data_loaded)
		std::cout << matrix.to_string();
	getchar();
	getchar();
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

void Menu::algorithm_menu()
{
	clear_term();
	std::string subtitles[] = { "Brute Force", "Branch and Bound - Best First Search",
		"Branch and Bound - Depth First Search", "Programowanie Dynamiczne", "Uruchom wszystkie" ,"Powrot" };
	int choice = 4;
	bool exit = false;
	while (!exit)
	{
		draw_menu(subtitles, 6, "Algorytmy");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			clear_term();
			std::cout << matrix.to_string();
			auto brutef{ tsp::brute_force(matrix) };
			run_algo<tsp::brute_force>(&tsp::brute_force::run, &brutef);
			getchar();
			getchar();
			break;
		}
		case 2:
		{
			clear_term();
			std::cout << matrix.to_string();
			auto bnb{ tsp::branch_n_bound(matrix) };
			run_algo<tsp::branch_n_bound>(&tsp::branch_n_bound::bfs, &bnb);
			break;
		}
		case 3:
		{
			clear_term();
			std::cout << matrix.to_string();
			auto bnb{ tsp::branch_n_bound(matrix) };
			run_algo<tsp::branch_n_bound>(&tsp::branch_n_bound::dfs, &bnb);
			break;
		}
		case 4:
		{
			clear_term();
			std::cout << matrix.to_string();
			auto hk{ tsp::held_karp(matrix) };
			run_algo<tsp::held_karp>(&tsp::held_karp::run, &hk);
			break;
		}
		case 5:
		{
			clear_term();
			std::cout << matrix.to_string();
			run_all_algos();
			break;
		}
		/*case 6:
		{
			clear_term();
			std::cout << "Sample:";
			int sample{0};
			std::cin >> sample;
			std::cout << "Nodes:";
			int nodes{0};
			std::cin >> nodes;
			timing(sample, nodes);
			getchar();
			getchar();
			break;
		}*/
		default:
		{
			exit = true;
			break;
		}
		}
	}
}

void Menu::run_all_algos()
{
	auto bf{ tsp::brute_force(matrix) };
	auto bnb{ tsp::branch_n_bound(matrix) };
	auto hk{ tsp::held_karp(matrix) };

	run_algo<tsp::brute_force>(&tsp::brute_force::run, &bf);
	run_algo<tsp::branch_n_bound>(&tsp::branch_n_bound::bfs, &bnb);
	run_algo<tsp::branch_n_bound>(&tsp::branch_n_bound::dfs, &bnb);
	run_algo<tsp::held_karp>(&tsp::held_karp::run, &hk);
	getchar();
	getchar();
}

std::vector<std::vector<int>> Menu::generate_random(int nodes)
{
	int number{0};
	std::vector<std::vector<int>> graph;
	graph.resize(nodes, std::vector<int>(nodes, 0));
	for(size_t i{0}; i < graph.size(); ++i)
	{
		for(size_t j{0}; j < graph.size(); ++j)
		{
			if (i != j)
				graph[i][j] = rand() % 100;
		}
	}
	return graph;
}

/*void Menu::timing(int sample, int nodes)
{
	double average_time{ 0 };
	double time{ 0 };
	int denied{ 0 };
	for (int i{ 0 }; i < sample; ++i)
	{
		matrix = Adjacency_Matrix( generate_random(nodes));
		auto bf{ tsp::brute_force(matrix) };
		auto t{ Timer<tsp::brute_force, Path>(&tsp::brute_force::run, &bf) };
		time = t.run();
		average_time += time;
		if (time > 120000)
		{
			std::cout << "\n at " << i << "denied\n";
			denied++;
		}
			
		//std::cout << "Pomiar: " << i << ", czas[ms]: " << time << std::endl;
	}
	std::cout << "Sredni pomiar[ms]: " << average_time / static_cast<double>(sample) << ", odrzucono: " << denied << std::endl;
}*/
