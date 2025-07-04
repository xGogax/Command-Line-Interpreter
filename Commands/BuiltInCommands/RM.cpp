#include "RM.h"

string RM::execute(string argument) {
    if (remove(argument.c_str()) == 0) {
        return "";
    } else {
        return "ERROR: File not found";
    }
}

string RM::checkOption(string opt) {
    if (opt.empty()) return opt;
    else return "ERROR";
}

string RM::checkCreateFile(string createFile) {
    if (createFile.empty()) return "";
    else return "ERROR";
}

string RM::checkArgument(string argument) {
    if (argument.empty()) return "ERROR";
    else return argument;
}
