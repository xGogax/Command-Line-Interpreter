#include "Parser.h"

string Parser::getCommand(string& line) {
    size_t pos = line.find(' ');
    string returnValue;

    if (pos != string::npos) {
        returnValue = line.substr(0, pos);
        line.erase(0, pos + 1);
    } else {
        returnValue = line;
        line.clear();
    }

    return returnValue;
}

string Parser::getOption(string &line) {
    if (line.empty()) return "";

    size_t pos = line.find(' ');
    string option;

    if (pos != string::npos) {
        option = line.substr(0, pos);
    } else {
        option = line;
    }

    bool inQuotes = false;
    for (char c : line) {
        if (c == '"') inQuotes = !inQuotes;
    }

    if (option[0] == '-' && !inQuotes) {
        if (pos != string::npos) {
            line.erase(0, pos + 1);
        } else {
            line.clear();
        }
        return option;
    }

    return "";
}

string Parser::getOutputFile(string &line) {
    if (line.empty()) return "";

    bool inQuotes = false;
    int lastSpacePos = -1;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        } else if (line[i] == ' ' && !inQuotes) {
            lastSpacePos = i;
        }
    }

    string lastWord;
    if (lastSpacePos != -1) {
        lastWord = line.substr(lastSpacePos + 1);
    } else {
        lastWord = line;
    }

    if (!lastWord.empty() && lastWord[0] == '>') {
        string fileName = lastWord.substr(1);

        if (lastSpacePos != -1) {
            line.erase(lastSpacePos);
        } else {
            line.clear();
        }

        return fileName;
    }

    return "";
}

string Parser::getArgument(string &line, bool fileContent) {
    if (line.empty()) return "";

    if (line[0] == '"') {
        size_t firstQuote = line.find('"');
        size_t lastQuote = line.find_last_of('"');

        if (lastQuote == string::npos || firstQuote == lastQuote) {
            return "";
        }

        string argument = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

        line.erase(0, lastQuote + 1);

        if (!line.empty() && line[0] == ' ') {
            line.erase(0, 1);
        }

        return argument;
    }

    // Ako je file argument
    string fileName = line;

    if (line[0] == '>') {
        fileName = line.substr(1);
    }

    line.clear();

    if (fileContent) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "ERROR: Unable to open file " << fileName << endl;
            return "ERROR";
        }

        string fileData;
        string lineFromFile;

        while (getline(file, lineFromFile)) {
            if (!fileData.empty()) {
                fileData += ' ';
            }
            fileData += lineFromFile;
        }

        file.close();

        return fileData;
    } else {
        return fileName;
    }
}

string Parser::getMultipleLines() {
    string result;
    string line;

    while (getline(cin, line)) {
        result += line + '\n';
    }

    cin.clear();

    return result;
}
