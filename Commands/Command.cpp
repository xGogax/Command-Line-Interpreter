#include "Command.h"

#include <iostream>
#include <fstream>

string Command::execute() {
    if(checkOption(opt) == "ERROR") return "ERROR";

    return execute(arg);
}
