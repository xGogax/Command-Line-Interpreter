#ifndef COMMAND_H
#define COMMAND_H

#include <string>

using namespace std;

class Command {
public:
    Command(string opt, string arg, string createFile) :
    opt(opt),
    arg(arg),
    createFile(createFile) {}

    virtual ~Command() = default;

    virtual string execute();
protected:
    string opt;
    string arg;
    string createFile;

    virtual string execute(string argument) = 0;
    virtual string checkOption(string opt) = 0;
private:
};

#endif
