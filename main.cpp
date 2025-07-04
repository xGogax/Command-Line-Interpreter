#include <iostream>

#include "Interpreter/Interpreter.h"

int main() {
    Interpreter* interpreter = new Interpreter();

    interpreter->start();

    delete interpreter;
    return 0;
}