#ifndef MISC_H
#define MISC_H
#include <iostream>

using namespace std;
#if defined(__linux__) || defined(__APPLE__)
    #define cls "clear"
#else
    #define cls "cls"
#endif

// system((mkdir+ "Users_Folder"))

void clearScreen()
{
    system(cls);
}

void pressEnter()
{
    cout << "Press enter to continue" << endl;
    cin.ignore(30, '\n');
    // cin.ignore();
}

#endif
