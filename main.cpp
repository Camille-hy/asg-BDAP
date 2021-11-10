#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "functions/F1.h"
#include "functions/F2.h"
#include "functions/F3.h"
#include "functions/F4.h"
#include "functions/misc.h"

using namespace std;


int main()
{
    //// Welcome Dashboard ////
    bool found = false;     // if Account is found
    bool isAdmin = false;   // if Found Account is Admin
    char choice;            // User's Choice
    char flag = true;       // Flag if True or False
    string name;            // User's Name

    Welcome_Screen();   // Show Welcome Screen
    Login_Choice(flag, isAdmin, name);     // Show Login Selection

    while(flag) // Flag remain true until user entered valid selection
    {
        Welcome_Screen();
        cout << "Invalid Choice!" << endl << endl;
        Login_Choice(flag, isAdmin, name);
    }
    
    // Determine if user is admin or user and log into respective menu
    if(isAdmin)
    {
        Admin_Menu(name);

    } 
    else 
    {
        while(true) // Remain in User Menu
        {
            User_Menu(name);
            choice = User_Menu_Selection(name);

            while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') // Bool remain true until user entered valid selection
                {
                    User_Menu(name);
                    cout << "Invalid Input" << endl;
                    choice = User_Menu_Selection(name);
                }
            

            if (choice == '1') // Statistical Analysis Menu
                {

                    while(true) // Remain in Statistical Analysis Menu
                    {
                        // Show Statistical Analysis Menu
                        Statistical_Analysis_Menu();
                        choice = Statistical_Analysis_Menu_Selection();

                        while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') // bool remain true until user entered valid selection
                        {
                            Statistical_Analysis_Menu();
                            cout << "Invalid Input" << endl;
                            choice = Statistical_Analysis_Menu_Selection();
                        }

                        if (choice == '1') //Statistical Calculation Menu
                        {
                            while(true) // Remain in Statistical Calculation Menu
                            {
                                // Show Statistical Calculation Menu
                                Statistical_Calculation_Menu();
                                choice = Statistical_Calculation_Menu_Selection();

                                while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7') // bool remain true until user entered valid selection
                                {
                                    Statistical_Calculation_Menu();
                                    cout << "Invalid Input" << endl;
                                    choice = Statistical_Calculation_Menu_Selection();
                                }

                                if (choice == '1')
                                {
                                    // Find Minimum

                                }
                                else if (choice == '2')
                                {
                                    // Find Maximum
                                }
                                else if (choice == '3')
                                {
                                    // Find Median

                                }
                                else if (choice == '4')
                                {
                                    // Find Mean
                                    
                                }
                                else if (choice == '5')
                                {
                                    // Find Variance
                                
                                }
                                else if (choice == '6')
                                {
                                    // Find Standard Deviation
                                
                                }
                                else if (choice == '7')
                                {
                                    //Go Back
                                    break;
                                }
                            }
                                    
                                }
                                else if (choice == '2')
                                {
                                    //Plot histogram

                                }
                                else if (choice == '3')
                                {
                                    //Correlation

                                }
                                else if (choice == '4')
                                {
                                    //Distinct data members
                                    
                                }
                                else if (choice == '5')
                                {
                                    //Go Back
                                    break;
                                }

                    }
            
                }

            else if (choice == '2')
                {
                    // View Saved Report
                    Report_Menu();
                }
            else if (choice == '3')
                {
                    //View User log

                }
            else if (choice == '4')
                {
                    // Change Password
                    Menu_Dashboard();
                    UserChangePassword(name);
                    
                }
            else if (choice == '5')
                {
                    // Log out
                    cout << "Logging Out..." << endl;
                    pressEnter();
                    main();
                    break;
                }

        }

    }
    return 0;
}


