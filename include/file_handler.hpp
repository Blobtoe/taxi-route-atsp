#include <string>
#include <fstream>

template<typename T>
class File_Handler{
    
public:

    File_Handler() = delete;

    File_Handler(std::string filepath, bool(*file_fnc)(std::fstream& file, T& t));
    
    File_Handler& operator=(const File_Handler& rhs) = default;
    ~File_Handler() = default;

    bool run(T& t);

private:
    
    bool (*file_fnc_)(std::fstream& file, T& t);

    std::string filepath_;
    std::string error_;
};

template<typename T>
File_Handler<T>::File_Handler(std::string filepath, bool(*file_fnc)(std::fstream& file, T& t))
    : filepath_{filepath}, file_fnc_{file_fnc}
{}

template<typename T>
bool File_Handler<T>::run(T& t)
{
	std::fstream file;
	file.exceptions(std::fstream::failbit | std::fstream::badbit);

	try {
		file.open(filepath_);
		file_fnc_(file, t);
	}
	catch (const std::ios_base::failure&)
	{
		error_ = "The file could not be opened.";
		return false;
	}
    catch (const std::invalid_argument&)
    {
        error_ = "The file contents couldn't be parsed.";
        return false;
    }
	return true;
}