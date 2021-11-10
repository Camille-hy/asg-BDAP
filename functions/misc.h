#ifndef MISC_H
#define MISC_H
#include <iostream>

using namespace std;

// system((mkdir+ "Users_Folder"))

void clearScreen()
{
    system("cls");
}

void pressEnter()
{
    cout << "Press enter to continue" << endl;
    cin.ignore();
}

#endif
