#ifndef PROMPT_H
#define PROMPT_H
#include "../Command.h"

class Prompt : public Command {
public:
    Prompt(string option, string argument, string createFile)
    : Command(option, argument, createFile) {}
protected:
    virtual string execute(string argument) override;
    virtual string checkOption(string opt) override;

    virtual string checkCreateFile(string createFile) override;
    virtual string checkArgument(string argument) override;
};

#endif
