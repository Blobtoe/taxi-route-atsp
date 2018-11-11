#pragma once

#include "adjacency_matrix.hpp"
#include "path.hpp"

#include <fstream>
#include <string>
#include <vector>

class Menu{

public:

	Menu() = default;
	Menu& operator=(const Menu& rhs) = delete;

	~Menu() = default;
	
	void run(const std::string subtitles[], size_t size, const std::string title);

private:

	Adjacency_Matrix matrix;
	bool data_loaded = false;
	// Kazda linia w srodku menu posiada 7 dodatkowych znakow,
	// aby wszystkie wygladaly w ponizszy sposob:
	// | 1) ... |
	const int extra_chars = 7;

	void draw_menu(const std::string subtitles[], size_t size, const std::string title) const;
	void draw_title(const std::string& title, const unsigned max_line) const;
	void draw_body(const std::string subtitles[], size_t size, const unsigned max_line) const;
	std::string add_extra_chars(const std::string& line, const unsigned line_no, const unsigned max_len) const;
	void clear_term() const;
	int longest_subtitle(const std::string subtitles[], size_t size) const;
	
	void handle_input(const std::string subtitles[], size_t size, std::string title);
	void get_filename();
	void display_matrix();
	void load_from_file(std::string& filename);

	void algorithm_menu();

	template<typename T>
	void run_algo(Path(T::*fnc)(), T* context);

	std::vector<std::vector<int>> generate_random(int node);
};

template<typename T>
void Menu::run_algo(Path(T::*fnc)(), T* context)
{
	auto t{ Timer<T, Path>(fnc, context) };

	std::cout << matrix.to_string();
	double time{ t.run() };
	std::cout << t.get_output().to_string();
	std::cout << "  Time[ms] >> " << time << std::endl;
	getchar();
	getchar();
}