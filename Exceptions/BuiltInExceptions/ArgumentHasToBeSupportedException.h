#ifndef ARGUMENTHASTOBESUPPORTEDEXCEPTION_H
#define ARGUMENTHASTOBESUPPORTEDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class ArgumentHasToBeSupportedException : public Exception {
public:
    ArgumentHasToBeSupportedException(const std::string& command) : Exception("ERROR: Command [" + command + "] cannot be executed without an argument") {}
};

#endif
