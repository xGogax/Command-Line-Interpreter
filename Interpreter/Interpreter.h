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

            try {
                command = Parser::parse(input);

                if (command != nullptr) {
                    string executedCommand = command->execute();
                    if (!executedCommand.empty()) cout << executedCommand << endl;
                }
            } catch (const Exception& e) {
                cout << e.what() << endl;
            }
        }
        delete command;
    };

    string getCommandPrompt(string commandPrompt);
    void setCommandPrompt(string commandPrompt);
private:
    static string commandPrompt;

    string getNextLine();
    void removeMultipleSpaces(string &input);
};

#endif
