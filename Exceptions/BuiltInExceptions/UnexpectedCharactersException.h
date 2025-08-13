#ifndef UNEXPECTEDCHARACTERSEXCEPTION_H
#define UNEXPECTEDCHARACTERSEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class UnexpectedCharactersException : public Exception {
public:
    UnexpectedCharactersException(const std::string& command, const std::string& characters)
    : Exception(makeMessage(command, characters)) {}
private:
    static std::string makeMessage(const std::string& command, const std::string& characters) {
        size_t pos = command.size() - characters.size();

        std::string marker(pos, ' ');

        for (char c : characters) {
            if (c == ' ')
                marker.push_back(' ');
            else
                marker.push_back('^');
        }

        return "ERROR: Unexpected characters:\n" + command + "\n" + marker;
    }
};

#endif
