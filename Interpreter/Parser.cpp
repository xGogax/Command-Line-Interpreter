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

            if (fileData.empty()) {
                emptyFile = false;
            }

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

        if (fileData.empty()) {
            emptyFile = false;
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

string* Parser::getTRArguments(string &line, bool fileContent) {
    string* args = new string[3]{"", "", ""}; // input, what, with
    vector<size_t> quotePositions;

    for (size_t i = 0; i < line.length(); ++i) {
        if (line[i] == '"' && (i == 0 || line[i - 1] != '\\')) {
            quotePositions.push_back(i);
        }
    }

    // Ako ima najmanje 4 navodnika - what i with postoje
    if (quotePositions.size() >= 4) {
        size_t q_with_close = quotePositions.back(); quotePositions.pop_back();
        size_t q_with_open = quotePositions.back(); quotePositions.pop_back();
        args[2] = line.substr(q_with_open + 1, q_with_close - q_with_open - 1);
        line.erase(q_with_open, q_with_close - q_with_open + 1);

        size_t q_what_close = quotePositions.back(); quotePositions.pop_back();
        size_t q_what_open = quotePositions.back(); quotePositions.pop_back();
        args[1] = line.substr(q_what_open + 1, q_what_close - q_what_open - 1);
        line.erase(q_what_open, q_what_close - q_what_open + 1);
    }

    // Ako ima tacno 2 navodnika - samo what postoji
    else if (quotePositions.size() == 2) {
        size_t q_what_close = quotePositions.back(); quotePositions.pop_back();
        size_t q_what_open = quotePositions.back(); quotePositions.pop_back();
        args[1] = line.substr(q_what_open + 1, q_what_close - q_what_open - 1);
        line.erase(q_what_open, q_what_close - q_what_open + 1);
    }

    // Ocisti visak razmaka
    while (!line.empty() && (line[0] == ' ' || line[0] == '\t')) line.erase(0, 1);
    while (!line.empty() && (line.back() == ' ' || line.back() == '\t')) line.pop_back();

    // Ako input postoji, obradi ga (moze biti string, <fajl ili ime fajla)
    if (!line.empty()) {
        if (line[0] == '"' && line.back() == '"') {
            args[0] = line.substr(1, line.length() - 2);
        } else if (line[0] == '<') {
            size_t i = 1;
            while (i < line.length() && line[i] == ' ') i++;
            string fileName = line.substr(i);
            if (fileContent) {
                ifstream file(fileName);
                if (!file.is_open()) {
                    cerr << "ERROR: Unable to open file " << fileName << endl;
                    args[0] = "ERROR";
                    return args;
                }
                string fileData, temp;
                while (getline(file, temp)) {
                    if (!fileData.empty()) fileData += '\n';
                    fileData += temp;
                }
                file.close();
                args[0] = fileData;
            } else {
                args[0] = fileName;
            }
        } else {
            if (fileContent) {
                ifstream file(line);
                if (!file.is_open()) {
                    cerr << "ERROR: Unable to open file " << line << endl;
                    args[0] = "ERROR";
                    return args;
                }
                string fileData, temp;
                while (getline(file, temp)) {
                    if (!fileData.empty()) fileData += '\n';
                    fileData += temp;
                }

                if (fileData.empty()) {
                    emptyFile = false;
                }

                file.close();
                args[0] = fileData;
            } else {
                args[0] = line;
            }
        }
    }

    // Ako je input prazan, a what i with nisu, izvrsi shift left
    if (args[0].empty() && !args[1].empty() && !args[2].empty()) {
        args[0] = args[1];
        args[1] = args[2];
        args[2] = "";
    }

    return args;
}
