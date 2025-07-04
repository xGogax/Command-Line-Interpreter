#ifndef TRUNCATE_H
#define TRUNCATE_H
#include "../Command.h"

class Truncate : public Command {
public:
    Truncate(string option, string argument, string createFile)
    : Command(option, argument, createFile){};
protected:
    string execute(string argument) override;
    string checkOption(string opt) override;

    string checkCreateFile(string createFile) override;
    string checkArgument(string argument) override;
};

#endif
