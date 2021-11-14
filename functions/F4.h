/* 
    All Functions in F4.h are implemented by 
    Student: TAN ZI SHENG (1201100837)
*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "misc.h"

using namespace std;

// Prototyping funtion Save_Report_Action
string Save_Report_Action();



// Function for centering text
// Effective Lines: 4
// In: user's name
// out: width needed to center the text 
int CenterText(string name)
{
    int length = name.size();
    int width = (52 / 2) + (length / 2);

    return width;
}

/* ========================================================== */

// Title Screen
// ------------

// This is the title screen that user will see when they first enter out program
// Effective lines: 7
// In: -
// Out: -
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
/* ========================================================== */


// Dashboard Screen
// ----------------

// This is the title used accross the whole progrma 
// Effective lines: 6 
// In: - 
// Out: - 
void Menu_Dashboard()
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;
}


// User options menu for login
// In: -
// Out: User's choice 
// Effective Lines: 10  
char Login_Dashboard()
{
    Menu_Dashboard();
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

/* ========================================================== */

// User options menu for statistical analysis  
// In: -
// Out: -
// Effective Lines: 6
void Statistical_Analysis_Menu()
{
    Menu_Dashboard();
    cout << "1.   Statistical Calculation" << endl;
    cout << "2.   Plot Histogram" << endl;
    cout << "3.   Correlation" << endl;
    cout << "4.   Distinct data members" << endl;
    cout << "5.   Go Back" << endl;
}


// Get User's input for statistical analysis menu
// In: -
// Out: User's choice
// Effective Lines: 5
char Statistical_Analysis_Menu_Selection()
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;
    cin.ignore(30, '\n');
    return user_choice;
}

// User option menu for statistical calculation
// In: -
// Out: -
// Effective Lines: 8
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

// Get User's input for statistical calculation menu
// In: -
// Out: User's choice
// Effective Lines: 5
char Statistical_Calculation_Menu_Selection()
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;
    cin.ignore(30, '\n');
    return user_choice;
}

/* ========================================================== */

// Generate titles with each computation's titles
// In: Computation titles (exp: HISTOGRAM, MEAN, MAXIMUM)
// Out: Beautiful titles ( with computation titles)
// Effective Lines: 11
string reportMethod(string method)
{
    stringstream ss;
    ss << "+";
    for (int i = 0; i < (method.length() + 4); i++)
    {
        ss << "-";
    }
    ss << "+" << endl;
    ss << "|  " + method + "  |" << endl;
    ss << "+";
    for (int i = 0; i < (method.length() + 4); i++)
    {
        ss << "-";
    }
    ss << "+" << endl;

    return ss.str();
}

/* ========================================================== */

// User Screen
// -----------

// Display list of options that user can choose from (for main_menu)
// In: User's name
// Out: -
// Effective Lines: 10
void User_Menu(string name)
{
    Menu_Dashboard();
    int width = CenterText(name);
    cout << setw(34) << "Welcome User, " << endl;
    cout << right << setw(width) << fixed << name << endl
         << endl;
    cout << "1.   Enter Statistical Analysis Menu" << endl;
    cout << "2.   View Saved Report" << endl;
    cout << "3.   View User Log" << endl;
    cout << "4.   Change Password" << endl;
    cout << "5.   Save file as other name" << endl;
    cout << "6.   Log out" << endl << endl;
}

// Get user's choice for user menu
// In: Uuser's name
// Out: User's choice
// Effective Lines: 3
char User_Menu_Selection(string name)
{
    char user_choice;
    cout << "Please Enter Your choice: ";
    cin >> user_choice;
    return user_choice;
}


// Get user's choice for save report menu
// In: -
// Out: User's choice
// Effective Lines: 11
string Save_Report_Menu()
{
    string user_choice;
    cout << "Do you want to save as report" << endl;
    cout << "Type 'y' save the report or 'n' to go back" << endl;
    while (true)
    {
        cout << "Please Enter Your Choice: ";
        getline(cin, user_choice);
        if (user_choice == "y")
        {
            user_choice = Save_Report_Action();
            break;
        }
        else if (user_choice == "n")
        {
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
            pressEnter();
        }
    }
    return user_choice;
}

// Menu for user to choose which report to view
// In: -
// Out: User's choice
// Effective Lines: 13
char Report_Menu()
{
    bool valid = true;
    char user_choice;
    Menu_Dashboard();
    cout << "1.   View plain text report" << endl;
    cout << "2.   View HTML report" << endl;
    cout << "3.   Go back" << endl;
    while (valid)
    {
        cout << "Please Enter Your choice: ";
        cin >> user_choice;
        cin.ignore(30, '\n');
        if (user_choice == '1' || user_choice =='2' || user_choice =='3') {
            valid = false;
        }
        else
        {
            cout << "Invalid Input" << endl;
            continue;
        }
    }
    return user_choice;
}



// Get User's input for which report to generate
// In: -
// Out: User's choice
// Effective Lines: 12
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

        if (user_choice == "1" || user_choice == "2" || user_choice == "3")
        {
            break;
        }
        else
        {
            cout << "Invalid input" << endl;
            pressEnter();
        }
    }
    return user_choice;
}


// Generate the report in HTML format
// In: method ( computation's title exp: HISTOGRAM), data in string form, title for computation exp: BIOLOGY, title2 (if there's another title)
// Out: Report in HTML format
// Effective Lines: 16
string Generate_HTML_Report(string method, string data, string title, string title2 = "")
{
    stringstream htmlData;
    string m = reportMethod(method);
    htmlData << "<html>" << endl;
    htmlData << "<body>" << endl;
    htmlData << "<h1>"
             << "<pre>" << m << "</pre>"
             << "</h1>" << endl;
    htmlData << "<h2>"
             << "Title: " << title;
    if (title2 != "")
    {
        htmlData << " & " << title2;
    }
    htmlData << "</h2>" << endl;
    htmlData << "<pre>" << data << "</pre>" << endl;
    htmlData << "</body>" << endl;
    htmlData << "</html>" << endl;
    return htmlData.str();
}


// Overload function for generating HTML Report which only accepts 2 arguments
// In: computation's method (exp : HISTOGRAM) , data in string format
// Out: Report in HTML format
// Effective Lines: 14
string Generate_HTML_Report(string method, string data)
{
    stringstream htmlData;
    string m = reportMethod(method);
    htmlData << "<html>" << endl;
    htmlData << "<body>" << endl;
    htmlData << "<h1>"
             << "<pre>" << m << "</pre>"
             << "</h1>" << endl;
    htmlData << "<h2>"
             << "All Titles"
             << "</h2>" << endl;
    htmlData << "<pre>" << data << "</pre>" << endl;
    htmlData << "</body>" << endl;
    htmlData << "</html>" << endl;
    return htmlData.str();
}

// Generate the report in plain text format
// In: method ( computation's title exp: HISTOGRAM), data in string form, title for computation exp: BIOLOGY, title2 (if there's another title)
// Out: Report in plain text format
// Effective Lines: 9
string Generate_Plain_Text_Report(string method, string data, string title, string title2 = "")
{
    stringstream plainTextData;
    string m = reportMethod(method);
    plainTextData << m << endl;
    plainTextData << "Title: " << title;
    if (title2 != "")
    {
        plainTextData << " & " << title2;
    }
    plainTextData << endl;
    plainTextData << data;
    return plainTextData.str();
}

// Overload function for generating plain text report which only accepts 2 arguments
// In: computation's method (exp : HISTOGRAM) , data in string format
// Out: Report in plain text format
// Effective Lines: 6
string Generate_Plain_Text_Report(string method, string data)
{
    stringstream plainTextData;
    string m = reportMethod(method);
    plainTextData << m << endl;
    plainTextData << "All Titles" << endl;
    plainTextData << data;
    return plainTextData.str();
}



/* ========================================================== */

// Admin screen
// ------------

// Display Admin Menu
// In: admin's name
// Out: -
// Effective Lines: 7
void Admin_Menu(string name)
{
    Menu_Dashboard();
    int width = CenterText(name);
    cout << right << setw(35) << "Welcome Admin, " << endl;
    cout << right << setw(width) << fixed << name << endl
         << endl;
    cout << "1.   Create User Account" << endl;
    cout << "2.   Modify User Account" << endl;
    cout << "3.   Log out" << endl;
}

// Get admin's selection for admin menu
// In: admin's name
// Out: admin's choice
// Effective Lines: 4
char Admin_Menu_Selection(string name)
{
    char admin_choice;
    cout << "Please Enter Your choice: ";
    cin >> admin_choice;
    return admin_choice;
}

// Menu for modifying user 
// In: -
// Out: -
// Effective Lines: 7
void Modify_User_Menu()
{
    clearScreen();
    bool valid = true;
    char user_choice;
    Menu_Dashboard();
    cout << "1.   Change Password" << endl;
    cout << "2.   Delete User Account" << endl;
    cout << "3.   Back" << endl;
}

// Menu for getting admin's input for modifying user menu
// In: -
// Out: admin's choice
// Effective Lines: 4
char Modify_User_Selection()
{
    char modify_choice;
    cout << "Please Enter Your choice: ";
    cin >> modify_choice;
    return modify_choice;
}




