#include "TR.h"

#include <iostream>
#include <sstream>
#include <string>

#include <sstream>

string TR::execute(string argument) {
    // Parsiranje argumenta u format: [input] "what" "with"
    size_t startInput = argument.find('[');
    size_t endInput = argument.find(']');
    if (startInput == string::npos || endInput == string::npos || endInput <= startInput) {
        return "ERROR: invalid input format";
    }
    string input = argument.substr(startInput + 1, endInput - startInput - 1);

    size_t firstQuote = argument.find('"', endInput);
    if (firstQuote == string::npos) return "ERROR: missing what";
    size_t secondQuote = argument.find('"', firstQuote + 1);
    if (secondQuote == string::npos) return "ERROR: invalid what";

    string what = argument.substr(firstQuote + 1, secondQuote - firstQuote - 1);

    size_t thirdQuote = argument.find('"', secondQuote + 1);
    string with;
    if (thirdQuote == string::npos) {
        with = "";
    } else {
        size_t fourthQuote = argument.find('"', thirdQuote + 1);
        if (fourthQuote == string::npos) return "ERROR: invalid with";
        with = argument.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);
    }

    stringstream ss(input);
    string token;
    string result;
    bool first = true;

    while (ss >> token) {
        if (token == what) {
            token = with;
        }
        if (!first) result += " ";
        result += token;
        first = false;
    }

    return result;
}

string TR::checkOption(string opt) {
    if (opt.empty()) {
        return opt;
    }
    return "ERROR";
}
