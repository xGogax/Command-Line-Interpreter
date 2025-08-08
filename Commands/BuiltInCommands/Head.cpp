#include "Head.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "../../Exceptions/BuiltInExceptions/OptionHasToBeSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/CommandFormatException.h"
#include "../../Exceptions/BuiltInExceptions/NumberCriteriaException.h"

string Head::execute(string argument) {
    int lineCount = 0;
    string numberPart = opt.substr(2);
    for (char c : numberPart) {
        if (c < '0' || c > '9') throw CommandFormatException(opt);
        lineCount = lineCount * 10 + (c - '0');
    }

    if (lineCount > 9999) throw NumberCriteriaException(lineCount, opt, 9999);

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
    if (opt.empty()) throw OptionHasToBeSupportedException("head");
    if (!(opt[0] == '-' && opt[1] == 'n')) throw OptionNotSupportedException(opt.substr(0, 2), "head");
    else return opt;
}
