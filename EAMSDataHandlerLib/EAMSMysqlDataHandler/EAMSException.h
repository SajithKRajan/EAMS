#pragma once
#include <exception>
#include <string>
class EAMSException : public _exception{
    const char* msg;
public :
    EAMSException(const char* msg) {
        this->msg = msg;
    }
    const char* what() const throw () {
        return this->msg;
    }
};

