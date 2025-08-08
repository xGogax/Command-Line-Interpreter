#ifndef CREATEFILENOTSUPPORTEDEXCEPTION_H
#define CREATEFILENOTSUPPORTEDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class CreateFileNotSupportedException : public Exception{
public:
    CreateFileNotSupportedException(const string& command) : Exception("ERROR: Command [" + command + "] does not support output redirection using > or >>") {}
};

#endif
