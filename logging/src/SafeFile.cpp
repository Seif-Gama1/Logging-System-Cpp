#include "SafeFile.hpp"

SafeFile::SafeFile(const std::string& filename, int flags){
    fd = open(filename.c_str(), flags);
    if (fd == -1){
        std::cout << "Error opening file: " << filename << std::endl; /* Testing */
    }
}

bool SafeFile::is_open(){
    if(fd != -1) return true;
    return false;
}

SafeFile::~SafeFile(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

SafeFile::SafeFile(SafeFile&& other)
    : fd(other.fd)
{
    other.fd = -1;
}

SafeFile& SafeFile::operator=(SafeFile&& other){
    if (this != &other) {
        if (fd != -1) {
            close(fd);
        }
        fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

ssize_t SafeFile::write(const void* buf, size_t size){
    if (fd != -1 ){
        return ::write(fd, buf, size);
    }
    return -1;
}

ssize_t SafeFile::read(void* buf, size_t size) {
    if (fd != -1) {
        return ::read(fd, buf, size);
    }
    return -1;
}

ssize_t SafeFile::readLine(std::string& out) {
    if (fd == -1) return -1;

    out.clear();
    char ch;
    ssize_t totalRead = 0;

    while (true) {
        ssize_t n = ::read(fd, &ch, 1);  // read one byte
        if (n == 0) { // EOF
            break;
        } else if (n < 0){ // error
            return -1;
        }
        totalRead += n;
        if (ch == '\n') break; 
        out += ch; 
    }

    if (out.empty() && totalRead == 0) {
        return 0; // EOF and nothing read
    }

    return totalRead;
}