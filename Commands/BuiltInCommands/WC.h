#ifndef WC_H
#define WC_H
#include "../Command.h"

class WC : public Command{
public:
    WC(string opt, string argument, string createFile)
    :Command(opt, argument, createFile){};

protected:
    string execute(string argument) override;
    string checkOption(string opt) override;
private:
    int countWords(string argument);
    int countCharacters(string argument);
};

#endif
