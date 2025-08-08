#include "Command.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "../Exceptions/Exception.h"

string Command::execute() {
    try {
        checkOption(opt);
        checkArgument(arg);
    } catch (const Exception& e) {
        cout << e.what() << endl;
        return "";
    }

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

