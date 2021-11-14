#ifndef MISC_H
#define MISC_H
#include <iostream>

using namespace std;
#if defined(__linux__) || defined(__APPLE__)
    #define cls "clear"
#else
    #define cls "cls"
#endif

// Clear Screen function
// In: -
// Out: -
// Effective lines: 1
void clearScreen()
{
    system(cls);
}

// Press enter function
// In: -
// Out: -
// Effective lines: 2
void pressEnter()
{
    cout << "Press enter to continue" << endl;
    cin.ignore(30, '\n');
}

#endif
