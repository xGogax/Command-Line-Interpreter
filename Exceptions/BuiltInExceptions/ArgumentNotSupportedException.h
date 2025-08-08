#ifndef ARGUMENTNOTSUPPORTEDEXCEPTION_H
#define ARGUMENTNOTSUPPORTEDEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class ArgumentNotSupportedException : public Exception {
public:
    ArgumentNotSupportedException(const std::string& command) : Exception("ERROR: Command [" + command + "] does not support any arguments") {}
};



#endif //ARGUMENTNOTSUPPORTEDEXCEPTION_H
