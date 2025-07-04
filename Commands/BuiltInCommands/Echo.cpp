#include "Echo.h"

string Echo::execute(string argument) {
    return argument;
}

string Echo::checkOption(string opt) {
    if(opt.empty()) {
        return opt;
    }

    return "ERROR";
}