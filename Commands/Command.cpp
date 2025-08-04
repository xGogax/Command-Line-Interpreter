#include "Command.h"

#include <iostream>
#include <fstream>
#include <filesystem>

string Command::execute() {
    if (checkOption(opt) == "ERROR") return "ERROR: option not found";
    if (checkArgument(arg) == "ERROR") return "ERROR: argument not supported / Missing argument";
    if (checkCreateFile(createFile) == "ERROR") return "ERROR: can't have >file with this command";

    if (createFile.empty()) return execute(arg);

    string result = execute(arg);
    ofstream file;

    string redirection = createFile.substr(0, 2);
    string actualFile;

    if (redirection == ">>") {
        actualFile = createFile.substr(3); // ">> "
        file.open(actualFile, ios::app);   // append
    } else if (createFile[0] == '>') {
        actualFile = createFile.substr(2); // "> "
        file.open(actualFile);             // overwrite
    } else {
        return "ERROR: invalid redirection format";
    }

    if (!file.is_open()) {
        return "ERROR Unable to open file";
    }

    file << result;
    file.close();
    return "";
}

