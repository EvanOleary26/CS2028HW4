#ifndef __EXCEPTIONS__H
#define __EXCEPTIONS__H

#include <iostream>

class Exception {
public:
    int errorNumber;
    std::string errorMessage;

    Exception() : errorNumber(0), errorMessage("") {};
    Exception(int errNum) : errorNumber(errNum) {};
    Exception(std::string errMess) : errorMessage(errMess) {};
    Exception(int errNum, std::string errMess) : errorNumber(errNum), errorMessage(errMess) {};

    void displayError() {
        std::cout << errorNumber << ": " << errorMessage << std::endl;
    }
};




#endif