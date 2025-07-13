#ifndef HEAD_H
#define HEAD_H
#include "../Command.h"

class Head : public Command{
public:
    Head(string option, string argument, string createFile)
    : Command(option, argument, createFile){};
protected:
    string execute(string argument) override;
    string checkOption(string opt) override;
};

#endif
