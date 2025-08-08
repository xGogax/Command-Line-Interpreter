#include "Time.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentNotSupportedException.h"

string Time::execute(string argument) {
    time_t now = time(0);
    tm *localTime = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << localTime->tm_hour << ":"
       << setfill('0') << setw(2) << localTime->tm_min << ":"
       << setfill('0') << setw(2) << localTime->tm_sec;

    return ss.str();
}

string Time::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "time");
    else return opt;
}

string Time::checkArgument(string argument) {
    if (!argument.empty()) throw ArgumentNotSupportedException("time");
    else return argument;
}
