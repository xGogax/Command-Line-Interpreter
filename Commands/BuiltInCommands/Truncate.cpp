#include "Truncate.h"

#include <fstream>

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentHasToBeSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/CreateFileNotSupportedException.h"

string Truncate::execute(string argument) {

    std::ofstream truncateFile(argument, std::ios::trunc);
    if (!truncateFile.is_open()) {
        return "ERROR";
    }
    truncateFile.close();

    return "";
}

string Truncate::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "truncate");
    else return opt;
}

string Truncate::checkCreateFile(string createFile) {
    if(!createFile.empty()) throw CreateFileNotSupportedException("truncate");
    else return createFile;
}

string Truncate::checkArgument(string argument) {
    if (argument.empty()) throw ArgumentHasToBeSupportedException("truncate");
    else return argument;
}
