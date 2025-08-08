#ifndef FILEALREADYEXISTEXCEPTION_H
#define FILEALREADYEXISTEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class FileAlreadyExistException : public Exception {
public:
    FileAlreadyExistException(const string& filename) : Exception("ERROR: File [" + filename + "] already exists") {}
};

#endif
