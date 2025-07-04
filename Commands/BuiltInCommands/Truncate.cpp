#include "Truncate.h"

#include <fstream>

string Truncate::execute(string argument) {
    ifstream checkFile(argument);
    if (!checkFile.is_open()) {
        return "ERROR";
    }
    checkFile.close();

    std::ofstream truncateFile(argument, std::ios::trunc);
    if (!truncateFile.is_open()) {
        return "ERROR";
    }
    truncateFile.close();

    return "";
}

string Truncate::checkOption(string opt) {
    if(opt.empty()) return opt;
    else return "ERROR";
}

string Truncate::checkCreateFile(string createFile) {
    if(createFile.empty()) return "";
    else return "ERROR";
}

string Truncate::checkArgument(string argument) {
    if (argument.empty()) return "ERROR";
    else return "";
}
