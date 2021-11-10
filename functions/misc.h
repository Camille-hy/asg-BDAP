#ifndef MISC_H
#define MISC_H
#include <iostream>
#if defined(__linux__) || defined(__APPLE__)
    #define cls "clear"
    #define mkdir "mkdir -p "
    #define slash "/"
#else
    #define cls "cls"
    #define mkdir "mkdir"
    #define slash "\\"
#endif

using namespace std;

// system((mkdir+ "Users_Folder"))

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
