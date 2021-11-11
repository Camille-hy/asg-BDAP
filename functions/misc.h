#ifndef MISC_H
#define MISC_H
#include <iostream>
#if defined(__linux__) || defined(__APPLE__)
    #define cls "clear"
#else
    #define cls "cls"
#endif

using namespace std;

void clearScreen()
{
    system("cls");
}

void pressEnter()
{
    cout << "Press enter to continue" << endl;
    cin.get();
}

#endif
