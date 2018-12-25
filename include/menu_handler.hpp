#pragma once

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"

#include <fstream>
#include <string>
#include <vector>

class Menu {
   public:
    Menu()        = default;
    Menu& operator=(const Menu& rhs) = delete;

    ~Menu() = default;

    void run(const std::string subtitles[], size_t size,
             const std::string title);

   private:
    Adjacency_Matrix matrix;
    bool data_loaded = false;

    const int format_chars = 7;  // = | 1) "..." |

    void draw_menu(const std::string subtitles[], size_t size,
                   const std::string title) const;
    void draw_title(const std::string& title, const unsigned max_line) const;
    void draw_body(const std::string subtitles[], size_t size,
                   const unsigned max_line) const;
    std::string align_line(const std::string& line, const unsigned line_no,
                           const unsigned max_len) const;
    void clear_term() const;
    int longest_subtitle(const std::string subtitles[], size_t size) const;

    void handle_input(const std::string subtitles[], size_t size,
                      std::string title);
    void get_filename();
    void display_matrix();
    void load_from_file(std::string& filename);
    void wait_for_reaction();

    void algorithm_menu();
    double run_algo(std::function<Path()> fnc);
    void run_all_algos();

    void time_menu();
    void time_bf(int sample, int nodes);
    void time_bnb_bfs(int sample, int nodes);
    void time_bnb_dfs(int sample, int nodes);
    void time_hk(int sample, int nodes);

    std::vector<std::vector<int>> generate_random(int node);
    std::vector<int> generate_row(std::vector<int>& row);
};