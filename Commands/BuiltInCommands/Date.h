#ifndef DATE_H
#define DATE_H

#include "../Command.h"

class Date : public Command {
public:
    Date(string opt, string argument, string createFile)
    : Command(opt, argument, createFile){};

protected:
    string execute(string argument) override;

    string checkOption(string opt) override;

    string checkArgument(string argument) override;
};

#endif
