#include "TR.h"

string TR::execute(string argument) {
    string result = arg;
    size_t pos = 0;

    if (what.empty()) {
        return result;
    }

    while ((pos = result.find(what, pos)) != string::npos) {
        result.replace(pos, what.length(), with);
        pos += with.length();
    }

    return result;
}


string TR::checkOption(string opt) {
    if (opt.empty()) return opt;
    else return "ERROR";
}
