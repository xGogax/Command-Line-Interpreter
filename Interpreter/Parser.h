#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include "../Commands/Command.h"

using namespace std;

class Parser {
public:
    static Command* parse(string& line);

private:
    static string getCommand(string& line);

    static string command;
    static string option;
    static string output;
    static string argument;
};

#endif
