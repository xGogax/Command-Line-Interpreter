#ifndef OPTIONNOTSUPPORTEDEXCEPTION_H
#define OPTIONNOTSUPPORTEDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class OptionNotSupportedException : public Exception{
public:
    OptionNotSupportedException(const std::string& option, const std::string& cmd) : Exception("ERROR: Command [" + cmd + "] does not support option " + option) {};
};

#endif
