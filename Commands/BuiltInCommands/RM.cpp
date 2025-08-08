#include "RM.h"

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/CreateFileNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentHasToBeSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/FileNotFoundException.h"

string RM::execute(string argument) {
    if (remove(argument.c_str()) == 0) {
        return "";
    } else {
        throw FileNotFoundException(argument);
    }
}

string RM::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "rm");
    else return opt;
}

string RM::checkCreateFile(string createFile) {
    if(!createFile.empty()) throw CreateFileNotSupportedException("rm");
    else return createFile;
}

string RM::checkArgument(string argument) {
    if (argument.empty()) throw ArgumentHasToBeSupportedException("rm");
    else return argument;
}
