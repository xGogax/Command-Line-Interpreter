#include "Touch.h"

#include <fstream>

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentHasToBeSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/CreateFileNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/FileAlreadyExistException.h"
#include "../../Exceptions/BuiltInExceptions/UnableToCreateFile.h"

string Touch::execute(string argument) {
    ifstream checkFile(argument);
    if (checkFile.is_open()) {
        checkFile.close();
        throw FileAlreadyExistException(argument);
    }

    ofstream file(argument);
    if (file.is_open()) {
        file.close();
    } else {
        throw UnableToCreateFile();
    }

    return "";
}

string Touch::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "truncate");
    else return opt;
}

string Touch::checkCreateFile(string createFile) {
    if(!createFile.empty()) throw CreateFileNotSupportedException("truncate");
    else return createFile;
}

string Touch::checkArgument(string argument) {
    if (argument.empty()) throw ArgumentHasToBeSupportedException("truncate");
    else return argument;
}


