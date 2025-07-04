#ifndef TOUCH_H
#define TOUCH_H

#include "../Command.h"

class Touch : public Command{
public:
    Touch(string option, string argument, string createFile)
    : Command(option, argument, createFile){};
protected:
    string execute(string argument) override;

    string checkOption(string opt) override;

    string checkCreateFile(string createFile) override;
    string checkArgument(string argument) override;
};

#endif
