#include "Batch.h"

#include <sstream>
#include <iostream>
using namespace std;

#include "../../Interpreter/Parser.h"

string Batch::execute(string argument) {
    stringstream ss(argument);
    string line;
    string result;

    while (getline(ss, line)) {
        if (line.empty()) continue;

        Command* command = Parser::parse(line);
        if (command) {
            result += command->execute() + "\n";
            delete command;
        }
    }

    if (!createFile.empty()) {
        ofstream out(createFile);
        if (!out) return "ERROR: Cannot open file " + createFile + " for writing";
        out << result;
        out.close();
    } else {
        cout << result;
    }

    return "";
}

string Batch::checkOption(string opt) {
    if (opt.empty()) return opt;
    return "ERROR";
}
