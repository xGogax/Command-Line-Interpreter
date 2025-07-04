#include "Touch.h"

#include <fstream>

string Touch::execute(string argument) {
    ifstream checkFile(argument);
    if (checkFile.is_open()) {
        checkFile.close();
        return "ERROR: File already exists";
    }

    ofstream file(argument);
    if (file.is_open()) {
        file.close();
    } else {
        return "ERROR: Unable to create file.";
    }

    return "";
}

string Touch::checkOption(string opt) {
    if(opt.empty()) {
        return opt;
    }
    //ERROR
    return "ERROR";
}

string Touch::checkCreateFile(string createFile) {
    if(createFile.empty()) {
        return "";
    }
    return "ERROR";
}

string Touch::checkArgument(string argument) {
    if(argument.empty()) {
        return "ERROR";
    }
    return "";
}


