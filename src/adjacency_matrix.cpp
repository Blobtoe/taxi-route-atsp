#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>> matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const std::string& filename)
	: a_matrix_{ std::vector<std::vector<int>>() }
{
	File_Handler<Adjacency_Matrix> f(filename, load_from_file);
	if(!f.run(*this))
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
		for(auto& cols: rows)
			output += std::to_string(cols) + " ";
		output += "\n";
	}
	return output;
}

bool Adjacency_Matrix::load_from_file(std::fstream& in_file, Adjacency_Matrix& matrix)
{
    std::string line;
    try
    {
		std::getline(in_file, line); // Skip the number of cities
        while(std::getline(in_file, line))
			matrix.a_matrix_.push_back( matrix.parse_file_input(line) );
    }
    catch(std::ifstream::failure& )
    {
        if(!in_file.eof())
			throw;
    }
	return true;
}

std::vector<int> Adjacency_Matrix::parse_file_input(std::string& line)
{
	auto output{ std::vector<int>() };
	for(auto& city: line)
	{
		if(city == (' '))
			continue;
		try{
			output.push_back(city - '0');
		}
		catch(const std::invalid_argument){ throw; }
	}
	return output;
}
