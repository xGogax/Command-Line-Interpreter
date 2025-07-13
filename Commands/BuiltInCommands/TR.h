#ifndef TR_H
#define TR_H

#include <string>

#include "../Command.h"

class TR : public Command{
public:
    TR(string opt, string arg, string createFile)
    : Command(opt, arg, createFile) {}
protected:
    string execute(string argument) override;

    string checkOption(string opt) override;

    bool shouldOverwriteFile() const override {
        return true;
    }

};

#endif
