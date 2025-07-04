#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>

#include "../Commands/Command.h"
#include "Parser.h"

using namespace std;

class Interpreter {
public:
    Interpreter()= default;
    ~Interpreter() = default;

    void start() {
        Command* command = nullptr;
        while (true) {
            cout << getCommandPrompt(commandPrompt);

            string input = getNextLine();
            if(input == "exit") {
                break;
            }
            removeMultipleSpaces(input);

            command = Parser::parse(input);

            cout << command->execute() << endl;
        }
        delete command;
    };

    string getCommandPrompt(string commandPrompt);
private:
    string commandPrompt = "$";

    string getNextLine();
    void removeMultipleSpaces(string &input);
};

#endif
