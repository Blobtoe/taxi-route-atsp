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
				std::cout << " Podaj ilosc wierzcholkow >> ";
				std::cin >> amount;
				matrix = Adjacency_Matrix(generate_random(amount));
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
			case 5:
			{
				time_menu();
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
		std::cout << "\n Podano nieprawidlowy plik.";
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
		"Branch and Bound - Depth First Search", "Programowanie Dynamiczne", "Uruchom wszystkie" ,"Powrot" };
	int choice = 4;
	bool exit = false;
	double time{ 0.0 };
	while (!exit)
	{
		draw_menu(subtitles, 6, "Algorytmy");
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
			std::cout << "  Time [ms] >> " << time;
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

	run_algo([&bf](){
		return bf.run();
	});

	run_algo([&bnb](){
		return bnb.best_fs();
	});

	run_algo([&bnb](){
		return bnb.dfs();
	});

	run_algo([&hk](){
		return hk.run();
	});
}

void Menu::time_menu()
{
	std::string subtitles[] = {"Brute Force", "Branch and Bound - Best First Search",
		"Branch and Bound - Depth First Search", "Programowanie Dynamiczne", "Powrot"};
	bool exit = false;
	int choice{5}, sample{0}, nodes{0};

	while(!exit)
	{
		clear_term();
		draw_menu(subtitles, 5, "Pomiary");
		std::cin >> choice;
		if(choice < 5)
		{
			std::cout << " Liczba pomiarow >> ";
			std::cin >> sample;
			std::cout << " Wielkosc grafu >> ";
			std::cin >> nodes;
		}
		switch(choice)
		{
			case 1:
			{
				time_bf(sample, nodes);
				wait_for_reaction();
				break;
			}
			case 2:
			{
				time_bnb_bfs(sample, nodes);
				wait_for_reaction();
				break;
			}
			case 3:
			{
				time_bnb_dfs(sample, nodes);
				wait_for_reaction();
				break;
			}
			case 4:
			{
				time_hk(sample, nodes);
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

void Menu::time_bf(int sample, int nodes)
{
	double average_time{ 0.0 };
	double time{ 0.0 };
	int denied{ 0 };
	for (int i{0} ; i < sample ; ++i)
	{
		auto graph{ Adjacency_Matrix(generate_random(nodes)) };
		auto bf{ tsp::brute_force(graph) };
		auto t{ Timer<Path>([&bf]() {
					return bf.run();
		}) };
		time = t.run();
		if (time > 300000)
			denied++;
		else
			average_time += time;
	}
	std::cout << "\n Sredni czas wykonania [ms] >> " << average_time / static_cast<double>(sample);
	std::cout << "\n Odrzucono >> " << denied;
}

void Menu::time_bnb_bfs(int sample, int nodes)
{
	double average_time{ 0.0 };
	double time{ 0.0 };
	int denied{ 0 };
	for (int i{ 0 }; i < sample; ++i)
	{
		auto graph{ Adjacency_Matrix(generate_random(nodes)) };
		auto bnb{ tsp::branch_n_bound(graph) };
		auto t{ Timer<Path>([&bnb]() {
					return bnb.best_fs();
		}) };
		time = t.run();
		if (time > 300000)
			denied++;
		else
			average_time += time;
	}
	std::cout << "\n Sredni czas wykonania [ms] >> " << average_time / static_cast<double>(sample);
	std::cout << "\n Odrzucono >> " << denied;
}

void Menu::time_bnb_dfs(int sample, int nodes)
{
	double average_time{ 0.0 };
	double time{ 0.0 };
	int denied{ 0 };
	for (int i{ 0 }; i < sample; ++i)
	{
		auto graph{ Adjacency_Matrix(generate_random(nodes)) };
		auto bnb{ tsp::branch_n_bound(graph) };
		auto t{ Timer<Path>([&bnb]() {
					return bnb.dfs();
		}) };
		time = t.run();
		if (time > 300000)
			denied++;
		else
			average_time += time;
	}
	std::cout << "\n Sredni czas wykonania [ms] >> " << average_time / static_cast<double>(sample);
	std::cout << "\n Odrzucono >> " << denied;
}

void Menu::time_hk(int sample, int nodes)
{
	double average_time{ 0.0 };
	double time{ 0.0 };
	int denied{ 0 };
	for (int i{ 0 }; i < sample; ++i)
	{
		auto graph{ Adjacency_Matrix(generate_random(nodes)) };
		auto hk{ tsp::held_karp(graph) };
		auto t{ Timer<Path>([&hk]() {
					return hk.run();
		}) };
		time = t.run();
		if (time > 300000)
			denied++;
		else
			average_time += time;
	}
	std::cout << "\n Sredni czas wykonania [ms] >> " << average_time / static_cast<double>(sample);
	std::cout << "\n Odrzucono >> " << denied;
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