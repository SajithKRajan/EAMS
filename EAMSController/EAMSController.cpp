#include <iostream>
#include "Source/CommandParser.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    CommandParser* cp = cp->getInstance();
    Command* cmd = cp->getCommand("VIEW_EMPLOYEE_DETAILS");
    cout << endl;
}

