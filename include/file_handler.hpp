#include <string>
#include <fstream>

class File_Handler{
    
public:

    File_Handler() = delete;
    File_Handler(std::string filepath);
    File_Handler& operator=(const File_Handler& rhs) = default;
    ~File_Handler() = default;

    bool run(bool (*file_fnc)(std::fstream& file));

private:
    std::string filepath_;
    std::string error_;
};


