#include "Date.h"

#include <ctime>
#include <iomanip>

#include "../../Exceptions/BuiltInExceptions/OptionNotSupportedException.h"
#include "../../Exceptions/BuiltInExceptions/ArgumentNotSupportedException.h"

string Date::execute(string argument) {
    time_t now = time(0);
    tm *localTime = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << localTime->tm_mday << "-"
    << setfill('0') << setw(2) << (localTime->tm_mon + 1) << "-"
    << setfill('0') << setw(4) << (localTime->tm_year + 1900);

    return ss.str();
}

string Date::checkOption(string opt) {
    if(!opt.empty()) throw OptionNotSupportedException(opt, "date");
    else return opt;
}

string Date::checkArgument(string argument) {
    if (!argument.empty()) throw ArgumentNotSupportedException("date");
    else return argument;
}
