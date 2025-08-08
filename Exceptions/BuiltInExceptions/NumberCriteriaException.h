#ifndef NUMBERCRITERIAEXCEPTION_H
#define NUMBERCRITERIAEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class NumberCriteriaException : public Exception {
public:
    NumberCriteriaException(const int& num, const string& opt, const int& criteria)
    : Exception("ERROR: Number [" + std::to_string(num) + "] in option [" + opt + "] exceeds the maximum allowed value (" + std::to_string(criteria) + ")") {}
};

#endif
