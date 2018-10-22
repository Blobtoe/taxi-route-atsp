#include "../include/file_handler.hpp"

File_Handler::File_Handler(std::string filepath)
	: filepath_{ filepath }
{}

bool File_Handler::run(bool(*file_fnc)(std::fstream& file))
{
	std::fstream file;
	file.exceptions(std::fstream::failbit | std::fstream::badbit);

	try {
		file.open(filepath_);
		file_fnc(file);
	}
	catch (const std::ios_base::failure& e)
	{
		error_ = e.what();
		return false;
	}
}