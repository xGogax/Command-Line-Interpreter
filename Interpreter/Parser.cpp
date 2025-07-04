#include "Parser.h"

Command* Parser::parse(string& line) {
    command = getCommand(line);
    cout << command << endl;
    return nullptr;
}

string Parser::getCommand(string& line) {
    size_t pos = line.find(' ');
    string returnValue;

    if (pos != string::npos) {
        returnValue = line.substr(0, pos);
        line.erase(0, pos + 1);
    } else {
        returnValue = line;
        line.clear();
    }

    return returnValue;
}
