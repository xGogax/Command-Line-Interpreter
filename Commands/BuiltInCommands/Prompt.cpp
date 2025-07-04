#include "Prompt.h"

#include "../../Interpreter/Interpreter.h"

string Prompt::execute(string argument) {
    Interpreter interpreter;
    interpreter.setCommandPrompt(argument);
    return "";
}

string Prompt::checkOption(string opt) {
    if (opt.empty()) return opt;
    else return "ERROR";
}

string Prompt::checkCreateFile(string createFile) {
    if (createFile.empty()) return "";
    return "ERROR";
}

string Prompt::checkArgument(string argument) {
    if (argument.empty()) return "ERROR";
    return "";
}
