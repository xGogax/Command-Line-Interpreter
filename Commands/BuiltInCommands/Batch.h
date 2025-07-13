#ifndef BATCH_H
#define BATCH_H
#include "../Command.h"

class Batch : public Command{
public:
    Batch(string option, string argument, string createFile)
    : Command(option, argument, createFile) {}
protected:
    string execute(string argument) override;
    string checkOption(string opt) override;
};

#endif
