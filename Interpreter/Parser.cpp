#include "Parser.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

bool pipe = false;

bool Parser::emptyFile = false;

void Parser::pipeSystem(string& line) {
    vector<string> segments;

    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        size_t start = segment.find_first_not_of(" \t");
        size_t end = segment.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            segment = segment.substr(start, end - start + 1);
        else
            segment = "";

        segments.push_back(segment);
    }

    string newArg = "";
    for (size_t i = 0; i < segments.size(); i++) {
        size_t firstSpace = segments[i].find(' ');
        size_t secondSpace = (firstSpace == std::string::npos) ? std::string::npos : segments[i].find(' ', firstSpace + 1);

        string option = tryOption(segments[i]);
        bool hasOption = (option != "");
        bool isFirstSegment = (i == 0);

        if (hasOption && !isFirstSegment) {
            // Ubacivanje sa navodnicima, na mesto posle secondSpace ili na kraj ako ne postoji
            if (secondSpace != std::string::npos) {
                segments[i].insert(secondSpace + 1, "\"" + newArg + "\"" + " ");
            } else {
                segments[i] += " \"" + newArg + "\"";
            }
        } else if (!hasOption && !isFirstSegment) {
            // Ubacivanje sa navodnicima, na mesto posle firstSpace ili na kraj ako ne postoji
            if (firstSpace != std::string::npos) {
                segments[i].insert(firstSpace + 1, "\"" + newArg + "\"" + " ");
            } else {
                segments[i] += " \"" + newArg + "\"";
            }
        } else if (hasOption && isFirstSegment) {
            // Ubacivanje bez navodnika, na mesto posle secondSpace ili na kraj ako ne postoji
            if (secondSpace != std::string::npos) {
                segments[i].insert(secondSpace + 1, newArg);
            } else {
                segments[i] += " " + newArg;
            }
        } else {
            // Ubacivanje bez navodnika, na mesto posle firstSpace ili na kraj ako ne postoji
            if (firstSpace != std::string::npos) {
                segments[i].insert(firstSpace + 1, newArg);
            } else {
                segments[i] += " " + newArg;
            }
        }

        Command* command = Parser::parse(segments[i]);
        if (i == segments.size() - 1) {
            cout << command->execute() << endl;
        } else {
            newArg = command->execute();
        }
        delete command;
    }
}

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

string Parser::tryOption(const string& line) {
    bool inQuotes = false;
    stringstream ss(line);
    string token;

    while (ss >> token) {
        for (char c : token) {
            if (c == '"') inQuotes = !inQuotes;
        }
        if (!inQuotes && token.size() > 1 && token[0] == '-') {
            return token;
        }
    }

    return "";
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
    int gtPos = -1;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        } else if (line[i] == '>' && !inQuotes) {
            gtPos = i;
            break;
        }
    }

    if (gtPos != -1) {
        int arrowLen = 1;
        if (gtPos + 1 < line.length() && line[gtPos + 1] == '>') {
            arrowLen = 2;
        }

        int i = gtPos + arrowLen;
        while (i < line.length() && line[i] == ' ') i++;

        if (i < line.length()) {
            string fileName = line.substr(i);
            line.erase(gtPos);
            return string(gtPos + arrowLen == gtPos + 2 ? ">> " : "> ") + fileName;
        }
    }

    return "";
}

string Parser::getArgument(string &line, bool fileContent) {
    if (line.empty()) return "";

    // " "
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

    emptyFile = true;
    // <file.txt or < file.txt
    string fileName = line;

    if (line[0] == '<') {
        // preskoči <
        size_t i = 1;
        while (i < line.length() && line[i] == ' ') i++;

        fileName = line.substr(i);
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
                    fileData += '\n';
                }
                fileData += lineFromFile;
            }

            file.close();
            return fileData;
        } else {
            return fileName;
        }
    }

    //file
    fileName = line;
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
                fileData += '\n';
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

string Parser::getTRArguments(string &line) {
    size_t firstQuote = line.find('"');

    string input;
    string what, with;

    if (firstQuote == 0) {
        // Format: "Hello World" "Hello" "Hi" or "Hello World" "Hello"
        size_t secondQuote = line.find('"', firstQuote + 1);
        if (secondQuote == string::npos) return "ERROR";
        input = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);

        size_t thirdQuote = line.find('"', secondQuote + 1);
        size_t fourthQuote = line.find('"', thirdQuote + 1);
        if (thirdQuote == string::npos || fourthQuote == string::npos) return "ERROR";
        what = line.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);

        size_t fifthQuote = line.find('"', fourthQuote + 1);
        if (fifthQuote == string::npos) {
            // nema with
            with = "";
        } else {
            size_t sixthQuote = line.find('"', fifthQuote + 1);
            if (sixthQuote == string::npos) return "ERROR";
            with = line.substr(fifthQuote + 1, sixthQuote - fifthQuote - 1);
        }
    } else {
        // Format: input.txt "Hello" "Hi" or input.txt "Hello"
        size_t space = line.find(' ');
        if (space == string::npos) return "ERROR";
        string fileName = line.substr(0, space);
        ifstream in(fileName);
        if (!in.is_open()) return "ERROR";
        stringstream buffer;
        buffer << in.rdbuf();
        input = buffer.str();
        in.close();
        line = line.substr(space + 1); // Remove filename from line

        size_t firstQ = line.find('"');
        size_t secondQ = line.find('"', firstQ + 1);
        if (firstQ == string::npos || secondQ == string::npos) return "ERROR";
        what = line.substr(firstQ + 1, secondQ - firstQ - 1);

        size_t thirdQ = line.find('"', secondQ + 1);
        if (thirdQ == string::npos) {
            // nema with
            with = "";
        } else {
            size_t fourthQ = line.find('"', thirdQ + 1);
            if (fourthQ == string::npos) return "ERROR";
            with = line.substr(thirdQ + 1, fourthQ - thirdQ - 1);
        }
    }

    return "[" + input + "]" + " \"" + what + "\" \"" + with + "\"";
}
