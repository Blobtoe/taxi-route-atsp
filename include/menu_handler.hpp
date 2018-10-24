#pragma once
#include <fstream>
#include <string>
#include <vector>

class Menu{

public:

	Menu() = default;
	Menu& operator=(const Menu& rhs) = delete;

	Menu(bool (*file_fnc)(std::fstream&));	// add a structure reference
	~Menu() = default;
	
	void draw(const std::string subtitles[], size_t size, const std::string title);

private:

	bool (*file_fnc_)(std::fstream&);
	// structure reference here

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
};