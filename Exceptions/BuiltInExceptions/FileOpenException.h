#ifndef FILEOPEN_H
#define FILEOPEN_H

#include <exception>
#include <string>

#include "../Exception.h"

class FileOpenException : public Exception {
public:
    FileOpenException(const std::string& filename) : Exception("ERROR: Unable to open file - " + filename) {};
};

#endif
