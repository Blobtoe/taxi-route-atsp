#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"
#include <iostream>

Adjacency_Matrix::Adjacency_Matrix()
{}

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>> matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const std::string& filename)
	: a_matrix_{ std::vector<std::vector<int>>() }
{
	File_Handler f(filename, *this);
	if(!f.run())
		throw std::invalid_argument("File couldn't be loaded");
}
 
bool Adjacency_Matrix::operator==(const Adjacency_Matrix& rhs) const
{
	if (a_matrix_ == rhs.a_matrix_)
		return true;
	return false;
}

bool Adjacency_Matrix::operator!=(const Adjacency_Matrix& rhs) const
{
    return !(*this==rhs);
}

const std::vector<int>& Adjacency_Matrix::operator[](const int index) const
{
    return a_matrix_.at(index);
}

int Adjacency_Matrix::size() const
{
    return a_matrix_.size();
}

std::string Adjacency_Matrix::to_string() const
{
	auto output{ std::string() };
	for(auto& rows: a_matrix_)
	{
		output += "| ";
		for(auto& cols: rows)
			output += std::string(2 - get_spaces(cols),' ') 
					+ std::to_string(cols) + " ";
		output += "|\n";
	}
	pretty_string(output);
	return output;
}

bool Adjacency_Matrix::load_from_file(std::fstream& in_file)
{
    std::string line;
    try
    {
		std::getline(in_file, line); // Skip the number of cities
        while(std::getline(in_file, line))
			a_matrix_.push_back( parse_file_input(line) );
    }
    catch(std::ifstream::failure& )
    {
        if(!in_file.eof())
			throw;
    }
	return true;
}

// Dostając jedną linię z pliku, konwertuje każdą z wag i dodaje do macierzy.
std::vector<int> Adjacency_Matrix::parse_file_input(std::string& line)
{
	auto output{ std::vector<int>() };
	int value{ 0 }, position{ 0 };
	std::string number;

	for (int i{ 0 }; i < line.size();)
	{
		position = line.find(" ", i);

		if (position == std::string::npos)
			position = line.size() - 1;

		value = std::stoi(line.substr(i, position));
		output.push_back(value);
		i = position + 1;
	}
	return output;
}

void Adjacency_Matrix::pretty_string(std::string& str_matrix) const
{
	size_t line_len{ str_matrix.size()/ a_matrix_.size() };
	std::string dashes{ std::string(line_len - 1, '-') + "\n"};
	str_matrix.insert(0, dashes);
	str_matrix.append(dashes);
}

int Adjacency_Matrix::get_spaces(const int number) const
{
	return number > 0 ? (int) log10((double) number) + 1 : 1;
}
