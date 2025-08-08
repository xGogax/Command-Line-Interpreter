#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include "../Exception.h"

class UnknownCommandException : public Exception {
public:
    UnknownCommandException(const std::string& command) : Exception("ERROR: Unknown command - " + command) {}
};

#endif
