#include "Echo.h"

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"

string Echo::execute(string argument) {
    return argument;
}

string Echo::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "echo");
    else return opt;
}