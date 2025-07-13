#ifndef PARSER_H
#define PARSER_H

#include <complex>
#include <iostream>
#include <fstream>

#include "../Commands/Command.h"
#include "../Commands/BuiltInCommands/Echo.h"
#include "../Commands/BuiltInCommands/Time.h"
#include "../Commands/BuiltInCommands/Date.h"
#include "../Commands/BuiltInCommands/Touch.h"
#include "../Commands/BuiltInCommands/WC.h"
#include "../Commands/BuiltInCommands/Prompt.h"
#include "../Commands/BuiltInCommands/Truncate.h"
#include "../Commands/BuiltInCommands/RM.h"
#include "../Commands/BuiltInCommands/TR.h"
#include "../Commands/BuiltInCommands/Head.h"
#include "../Commands/BuiltInCommands/Batch.h"

using namespace std;

class Parser {
public:
    static Command* parse(string& line) {
        string command;
        string option;
        string argument;
        string createFile;

        command = getCommand(line);
        option = getOption(line);
        createFile = getOutputFile(line);

        bool readFileContent = !(command == "touch" || command == "truncate" || command == "rm");
        if (command != "tr") argument = getArgument(line, readFileContent);
        if (argument == "ERROR") return nullptr;

        if(command == "echo") {
            if (argument == "")  argument = getMultipleLines();
            Echo* echo = new Echo(option, argument, createFile);
            return echo;
        } else if (command == "time") {
            Time* time = new Time(option, argument, createFile);
            return time;
        } else if (command == "date") {
            Date* date = new Date(option, argument, createFile);
            return date;
        } else if (command == "touch") {
            Touch* touch = new Touch(option, argument, createFile);
            return touch;
        } else if (command == "wc") {
            if (argument == "") argument = getMultipleLines();
            WC* wc = new WC(option, argument, createFile);
            return wc;
        } else if (command == "prompt") {
            Prompt* prompt = new Prompt(option, argument, createFile);
            return prompt;
        } else if (command == "truncate") {
            Truncate* truncate = new Truncate(option, argument, createFile);
            return truncate;
        } else if (command == "rm") {
            RM* rm = new RM(option, argument, createFile);
            return rm;
        } else if (command == "tr") {
            string fileCandidate;
            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                string firstToken = line.substr(0, spacePos);
                if (!firstToken.empty() && firstToken[0] != '"') {
                    ifstream testFile(firstToken);
                    if (testFile.is_open()) {
                        fileCandidate = firstToken;
                        testFile.close();
                    }
                }
            }

            argument = getTRArguments(line);

            if (createFile.empty() && !fileCandidate.empty()) {
                createFile = fileCandidate;
            }

            TR* tr = new TR(option, argument, createFile);
            return tr;
        } else if (command == "head") {
            Head* head = new Head(option, argument, createFile);
            return head;
        } else if (command == "batch") {
            if (argument == "")  argument = getMultipleLines();
            Batch* batch = new Batch(option, argument, createFile);
            return batch;
        }
        return nullptr;
    };

private:
    static string getCommand(string& line);
    static string getOption(string& line);
    static string getOutputFile(string& line);
    static string getArgument(string& line, bool fileContent);

    static string getMultipleLines();

    static string getTRArguments(string& line);
};

#endif
