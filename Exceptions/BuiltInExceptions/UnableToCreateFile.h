#ifndef UNABLETOCREATEFILE_H
#define UNABLETOCREATEFILE_H

#include <exception>
#include <string>

#include "../Exception.h"

class UnableToCreateFile : public Exception {
public:
    UnableToCreateFile() : Exception("ERROR: Unable to create file.") {}
};

#endif