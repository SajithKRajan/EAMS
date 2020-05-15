#pragma once
#include <exception>
#include <string>
#include <iostream>

class EAMSException : public std::exception {
    const char* msg;
public :
    EAMSException(const char* msg) {
        //std::cout << msg;
        this->msg = msg;
    }
    const char* what() const{
        return this->msg;
    }
};

