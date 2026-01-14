#include "FileSink.hpp"

FileSink::FileSink(const std::string& filename) 
    : file(filename, std::ios::app) 
{

}

/* Move constructor */
FileSink::FileSink(FileSink&& other) noexcept
    : file(std::move(other.file))
{
    
}

/* Move assignment */
FileSink& FileSink::operator=(FileSink&& other) noexcept{
    if (this != &other){ /* protect from self assignmnet */           
        if (file.is_open()){
            file.close();
        }
        file = std::move(other.file);
    }
    return *this;
}

void FileSink::write(const LogMessage& msg){
    if (file.is_open()) {
        file << msg << std::endl;
    }
}
