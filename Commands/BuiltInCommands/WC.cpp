#include "WC.h"

#include <sstream>

int WC::countWords(string argument) {
    if (argument.empty()) return 0;

    stringstream ss(argument);
    string word;
    int count = 0;

    while (ss >> word) {
        count++;
    }

    return count;
}
int WC::countCharacters(string argument) {
    return argument.length();
}

string WC::execute(string argument) {
    if(opt == "-w") {
        return to_string(countWords(argument));
    } else if (opt == "-c") {
        return to_string(countCharacters(argument));
    }
    return "ERROR";
}

string WC::checkOption(string opt) {
    if (opt == "-w") return opt;
    else if (opt == "-c") return opt;
    else return "ERROR";
}
