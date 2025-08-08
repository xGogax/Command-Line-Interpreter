#ifndef COMMANDFORMATEXCEPTION_H
#define COMMANDFORMATEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class CommandFormatException : public Exception {
public:
    CommandFormatException(const string& option) : Exception("ERROR: Option [" + option + "] has an invalid format") {}
};

#endif
