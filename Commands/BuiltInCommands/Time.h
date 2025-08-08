#ifndef TIME_H
#define TIME_H
#include "../Command.h"


class Time : public Command{
public:
    Time(string opt, string argument, string createFile)
    : Command(opt, argument, createFile){};

protected:
    string execute(string argument) override;

    string checkOption(string opt) override;

    string checkArgument(string argument) override;
};

#endif
