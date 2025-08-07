#ifndef TR_H
#define TR_H
#include "../Command.h"

class TR : public Command{
public:
    TR(string opt, string arg, string createFile, string what, string with) : Command(opt, arg, createFile) {
        this->with = with;
        this->what = what;
    }

    virtual string execute(string argument) override;
    virtual string checkOption(string opt) override;

private:
    string with;
    string what;
};

#endif
