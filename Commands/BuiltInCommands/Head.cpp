#include "Head.h"

#include <iostream>
#include <bits/ostream.tcc>

string Head::execute(string argument) {
    if (opt.size() < 3 || opt.substr(0, 2) != "-n")
        return "ERROR: invalid option format";

    int lineCount = 0;
    string numberPart = opt.substr(2);
    for (char c : numberPart) {
        if (c < '0' || c > '9') return "ERROR: invalid number in option";
        lineCount = lineCount * 10 + (c - '0');
    }

    if (lineCount > 9999) return "ERROR: number larger than 9999";

    string result;
    int currentLines = 0;

    for (size_t i = 0; i < argument.size(); ++i) {
        result += argument[i];

        if (argument[i] == '\n') {
            currentLines++;
            if (currentLines == lineCount)
                break;
        }
    }

    return result;
}

string Head::checkOption(string opt) {
    if (opt.empty()) return "ERROR";
    else return opt;
}
