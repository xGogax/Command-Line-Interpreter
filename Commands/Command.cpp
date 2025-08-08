#include "Command.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "../Exceptions/Exception.h"
#include "../Exceptions/BuiltInExceptions/FileOpenException.h"

string Command::execute() {
    try {
        checkOption(opt);
        checkArgument(arg);
        checkCreateFile(createFile);
    } catch (const Exception& e) {
        cout << e.what() << endl;
        return "";
    }

    //ukoliko treba da se ispise na konzolu
    if (createFile.empty()) return execute(arg);

    //ukoliko treba da se ispise u fajl
    string result = execute(arg);
    ofstream file;

    string redirection = createFile.substr(0, 2);
    string actualFile;

    if (redirection == ">>") {
        actualFile = createFile.substr(3); // ">> "
        file.open(actualFile, ios::app); // append
    } else if (createFile[0] == '>') {
        actualFile = createFile.substr(2); // "> "
        file.open(actualFile);                 // overwrite
    }

    if (!file.is_open()) {
        throw FileOpenException(actualFile);
    }

    file << result;
    file.close();
    return "";
}

