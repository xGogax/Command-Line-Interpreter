#ifndef ECHO_H
#define ECHO_H

#include "../Command.h"

using namespace std;

class Echo : public Command {
public:
    Echo(string opt, string arg, string createFile)
    : Command(opt, arg, createFile) {}

protected:
    string execute(string argument) override;

    string checkOption(string opt) override;
};



#endif //ECHO_H
