#ifndef F4_H
#define F4_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "misc.h"

using namespace std;
string Save_Report_Action();
void Welcome_Screen()
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                    Welcome to                    |" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;
}

void Menu_Dashboard()
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;
}

char Login_Dashboard()
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;
    cout << "Please Choose " << endl
         << endl;
    cout << "1. Login" << endl;
    cout << "2. Quit" << endl
         << endl;
    cout << "Please Enter your choice: ";
    char choice;
    cin >> choice;
    return choice;
}

void Statistical_Analysis_Menu()
{
    Menu_Dashboard();
    cout << "1.   Statistical Calculation" << endl;
    cout << "2.   Plot Histogram" << endl;
    cout << "3.   Correlation" << endl;
    cout << "4.   Distinct data members" << endl;
    cout << "5.   Go Back" << endl;
}

char Statistical_Analysis_Menu_Selection()
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;
    cin.ignore(30, '\n');
    return user_choice;
}

void Statistical_Calculation_Menu()
{
    Menu_Dashboard();
    cout << "1.   Minimum" << endl;
    cout << "2.   Maximum" << endl;
    cout << "3.   Median" << endl;
    cout << "4.   Mean" << endl;
    cout << "5.   Variance" << endl;
    cout << "6.   Standard Deviation" << endl;
    cout << "7.   Go Back" << endl;
}

char Statistical_Calculation_Menu_Selection()
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;
    cin.ignore(30, '\n');
    return user_choice;
}

void User_Menu(string name)
{
    Menu_Dashboard();

    cout << "Welcome User, " << name << endl
         << endl;
    cout << "1.   Enter Statistical Analysis Menu" << endl;
    cout << "2.   View Saved Report" << endl;
    cout << "3.   View User Log" << endl;
    cout << "4.   Change Password" << endl;
    cout << "5.   Log out" << endl;
}

string Save_Report_Menu()
{
    Menu_Dashboard();
    string user_choice;
    cout << "Do you want to save as report" << endl;
    cout << "Type 'y' save the report or 'n' to go back" << endl;

    while (true)
    {
        cout << "Please Enter Your Choice: ";
        getline(cin, user_choice);
        // cin.ignore(30, '\n');
        // cin.get(user_choice);

        if (user_choice == "y")
        {
            user_choice = Save_Report_Action();

            // if (user_choice == '3') {

            // }
            return user_choice;
            break;
        }
        else if (user_choice == "n")
        {
            return user_choice;
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
            // cin.ignore(50, '\n');
            pressEnter();
        }
    }
}

string Save_Report_Action()
{
    string user_choice;
    Menu_Dashboard();

    cout << "1. Generate Plain Text Report" << endl;
    cout << "2. Generate HTML Report" << endl;
    cout << "3. Go Back" << endl;

    while (true)
    {
        cout << "Please Enter Your Choice: ";
        getline(cin, user_choice);

        if (user_choice == "1")
        {
            return user_choice;
            break;
        }
        else if (user_choice == "2")
        {
            return user_choice;
            break;
        }
        else if (user_choice == "3")
        {
            Save_Report_Menu();
            break;
        }
        else
        {
            cout << "Invalid input" << endl;
            pressEnter();
        }
    }
}

string Generate_HTML_Report(string data)
{
    stringstream htmlData("data.html");
		
    htmlData << "<html>" << endl;
    htmlData << "<body>" << endl;
    htmlData << "<pre>" << data << "</pre>" << endl;
    htmlData << "</body>" << endl;
    htmlData << "</html>" << endl;
		return htmlData.str();
}

char User_Menu_Selection(string name)
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;

    if (user_choice == '1')
    {
        // Statistical Menu
        return '1';
    }

    else if (user_choice == '2')
    {
        // View Saved Report
        return '2';
    }

    else if (user_choice == '3')
    {
        // View User Log
        return '3';
    }

    else if (user_choice == '4')
    {
        // Change Password
        // UserChangePassword();
        return '4';
    }

    else if (user_choice == '5')
    {
        // Log out
        cin.ignore();
        return '5';
    }
}

void Modify_User_Menu()
{
    clearScreen();
    bool valid = true;
    char user_choice;
    Menu_Dashboard();
    cout << "1.   Change Password" << endl;
    cout << "2.   Delete User Account" << endl;
    cout << "3.   Back" << endl;

    while (valid)
    {
        cout << "Please Enter Your choice: ";
        cin >> user_choice;
        cin.ignore(30, '\n');

        if (user_choice == '1')
        {
            clearScreen();
            cout << "Change Password" << endl
                 << endl;
            cout << "Status 0 = Deleted, Status 1 = Active" << endl;
            cout << "Type 0 = User, Type 1 = Admin" << endl
                 << endl;
            AdminChangePassword();
            break;
        }
        else if (user_choice == '2')
        {
            clearScreen();
            cout << "Delete user account" << endl
                 << endl;
            cout << "Status 0 = Deleted, Status 1 = Active" << endl;
            cout << "Type 0 = User, Type 1 = Admin" << endl
                 << endl;
            UserDelete();
            break;
        }
        else if (user_choice == '3')
        {
            clearScreen();
            Admin_Menu("123");
            break;
        }
    }
}

char Report_Menu()
{
    bool valid;
    char user_choice;

    cout << "1.   View plain text report" << endl;
    cout << "2.   View HTML report" << endl;

    while (valid)
    {
        cout << "Please Enter Your choice: ";
        cin >> user_choice;
        cin.ignore(30, '\n');

        if (user_choice == '1')
        {
            return user_choice;
            // cout << "Plain Text Report" << endl;
        }

        else if (user_choice == '2')
        {
            // cout << "HTML Report" << endl;
            return user_choice;
        }

        else
        {
            cout << "Invalid Input" << endl;
            // return '0';
        }
    }
}

#endif