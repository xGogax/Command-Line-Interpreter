#include "WC.h"

#include <sstream>

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

string WC::execute(string argument) {
    if(opt == "-w") {
        return to_string(countWords(argument));
    } else if (opt == "-c") {
        return to_string(countCharacters(argument));
    }
}

string WC::checkOption(string opt) {
    if (opt.empty()) throw OptionHasToBeSupportedException("wc");
    if (opt != "-w" && opt != "-c") throw OptionNotSupportedException(opt, "wc");
    return opt;
}
