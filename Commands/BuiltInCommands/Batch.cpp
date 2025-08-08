#include "Batch.h"

#include <sstream>
#include <iostream>
using namespace std;

#include "../../Interpreter/Parser.h"

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/FileOpenException.h"

string Batch::execute(string argument) {
    stringstream ss(argument);
    string line;
    string result;

    while (getline(ss, line)) {
        if (line.empty()) continue;

        try {
            Command* command = Parser::parse(line);
            if (command != nullptr) {
                string executedCommand = command->execute();
                if (!executedCommand.empty()) result += executedCommand + "\n";
                delete command;
            }
        } catch (const Exception& e) {
            cout << e.what() << endl;
        }
    }

    if (!createFile.empty()) {
        ofstream out(createFile);
        if (!out) throw FileOpenException(createFile);
        out << result;
        out.close();
    } else {
        cout << result;
    }

    return "";
}

string Batch::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "batch");
    else return opt;
}
