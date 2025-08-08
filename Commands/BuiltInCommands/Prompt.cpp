#include "Prompt.h"

#include "../../Interpreter/Interpreter.h"

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/CreateFileNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentHasToBeSupportedException.h"

string Prompt::execute(string argument) {
    Interpreter interpreter;
    interpreter.setCommandPrompt(argument);
    return "";
}

string Prompt::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "prompt");
    else return opt;
}

string Prompt::checkCreateFile(string createFile) {
    if(!createFile.empty()) throw CreateFileNotSupportedException("prompt");
    else return createFile;
}

string Prompt::checkArgument(string argument) {
    if (argument.empty()) throw ArgumentHasToBeSupportedException("prompt");
    else return argument;
}
