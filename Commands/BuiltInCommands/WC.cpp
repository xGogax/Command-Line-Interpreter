#include "WC.h"

#include <sstream>
#include <iostream>

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/OptionHasToBeSupportedException.h"

int WC::countWords(const string &argument) {
    if (argument.empty()) return 0;

    stringstream ss(argument);
    string word;
    int count = 0;

    while (ss >> word) {
        count++;
    }

    return count;
}
int WC::countCharacters(const string &argument) {
    return argument.length();
}

int WC::countLines(const string &argument) {
    int counter = 0;
    for (int i = 0; i <= argument.length(); i++) {
        if (argument[i] == '\n') counter++;
    }
    return counter;
}

string WC::execute(string argument) {
    if(opt == "-w") {
        return to_string(countWords(argument));
    } else if (opt == "-c") {
        return to_string(countCharacters(argument));
    } else if (opt == "-l") {
        return to_string(countLines(argument));
    }
}

string WC::checkOption(string opt) {
    if (opt.empty()) throw OptionHasToBeSupportedException("wc");
    if (opt != "-w" && opt != "-c" && opt != "-l") throw OptionNotSupportedException(opt, "wc");
    return opt;
}
