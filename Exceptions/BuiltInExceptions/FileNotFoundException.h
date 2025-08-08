#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class FileNotFoundException : public Exception {
public:
    FileNotFoundException(const string& filename) : Exception("ERROR: File [" + filename + "] does not exist") {}
};

#endif
