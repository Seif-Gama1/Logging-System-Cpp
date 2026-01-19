#include "FileSink.hpp"

std::string FileSink::format(const LogMessage& msg) {
            std::ostringstream oss;
            oss << msg << '\n';
            return oss.str();
}


FileSink::FileSink(const std::string& path)
        : file(path.c_str(), O_WRONLY | O_APPEND | O_CREAT)
{

}

/* move constructor */
FileSink::FileSink(FileSink&& other)
    : file(std::move(other.file))
{
    
}

/* move assignment op */
FileSink& FileSink::operator=(FileSink&& other){
    if (this != &other){ /* protect from passing self */           
        file = std::move(other.file);
    }
    return *this;
}

void FileSink::write(const LogMessage& msg){
    auto text = format(msg);
    file.write(text.data(), text.size());
}
