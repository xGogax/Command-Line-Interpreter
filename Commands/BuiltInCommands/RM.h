#ifndef RM_H
#define RM_H
#include "../Command.h"

class RM : public Command{
public:
    RM(string option, string argument, string createFile)
    : Command(option, argument, createFile){};

protected:
    string execute(string argument) override;
    string checkOption(string opt) override;

    string checkCreateFile(string createFile) override;
    string checkArgument(string argument) override;
};

#endif
