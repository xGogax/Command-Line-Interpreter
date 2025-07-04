#include "Command.h"

#include <iostream>
#include <fstream>
#include <filesystem>

string Command::execute() {
    if(checkOption(opt) == "ERROR") return "ERROR: option not found";
    if(checkArgument(arg) == "ERROR") return "ERROR: argument not supported / Missing argument";
    if(checkCreateFile(createFile) == "ERROR") return "ERROR: can't have >file with this command";

    if(createFile.empty()) return execute(arg);

    string result = execute(arg);

    if (filesystem::exists(createFile)) {
        //if file exists
        ofstream file(createFile, ios::app);
        if (!file.is_open()) {
            return "ERROR Unable to open file";
        }
        file << endl << result;
        file.close();
    } else {
        //if file does not exist
        ofstream file(createFile);
        if (!file.is_open()) {
            return "ERROR Unable to open file";
        }
        file << result;
        file.close();
    }

    return "";
}
