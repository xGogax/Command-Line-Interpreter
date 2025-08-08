#ifndef OPTIONHASTOBESUPPORTEDEXCEPTION_H
#define OPTIONHASTOBESUPPORTEDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class OptionHasToBeSupportedException : public Exception{
public:
    OptionHasToBeSupportedException(const std::string& command) : Exception("ERROR: Command [" + command + "] cannot be executed without an option") {}
};

#endif
