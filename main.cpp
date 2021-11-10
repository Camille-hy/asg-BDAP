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
    bool found = false;   // if Account is found
    bool isAdmin = false; // if Found Account is Admin
    char choice;          // User's Choice
    char flag = true;     // Flag if True or False
    string name;          // User's Name

    Welcome_Screen();                  // Show Welcome Screen
    Login_Choice(flag, isAdmin, name); // Show Login Selection

    while (flag) // Flag remain true until user entered valid selection
    {
        Welcome_Screen();
        cout << "Invalid Choice!" << endl
             << endl;
        Login_Choice(flag, isAdmin, name);
    }

    // Determine if user is admin or user and log into respective menu
    if (isAdmin)
    {
        Admin_Menu(name);
    }
    else
    {
        Logger logger(name);
        File f(name);
        while (true) // Remain in User Menu
        {
            User_Menu(name);
            choice = User_Menu_Selection(name);

            while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') // Bool remain true until user entered valid selection
            {
                User_Menu(name);
                cout << "Invalid Input" << endl;
                choice = User_Menu_Selection(name);
            }

            if (choice == '1') // Statistical Analysis Menu
            {

                while (true) // Remain in Statistical Analysis Menu
                {
                    // Show Statistical Analysis Menu
                    Statistical_Analysis_Menu();
                    choice = Statistical_Analysis_Menu_Selection();

                    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') // bool remain true until user entered valid selection
                    {
                        Statistical_Analysis_Menu();
                        cout << "Invalid Input" << endl;
                        choice = Statistical_Analysis_Menu_Selection();
                    }

                    if (choice == '1') //Statistical Calculation Menu
                    {
                        while (true) // Remain in Statistical Calculation Menu
                        {
                            // Show Statistical Calculation Menu
                            Statistical_Calculation_Menu();
                            choice = Statistical_Calculation_Menu_Selection();

                            while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7') // bool remain true until user entered valid selection
                            {
                                Statistical_Calculation_Menu();
                                cout << "Invalid Input" << endl;
                                choice = Statistical_Calculation_Menu_Selection();
                            }

                            if (choice == '1')
                            {
                                // Find Minimum
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find Minimum for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_min(arr2d, row, index);
                                            cout << "Minimum of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_min(arr2d, row, i);
                                            cout << "Minimum of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '2')
                            {
                                // Find Maximum
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find Maximum for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_max(arr2d, row, index);
                                            cout << "Maximum of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_max(arr2d, row, i);
                                            cout << "Maximum of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '3')
                            {
                                // Find Median
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find Median for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_median(arr2d, row, index);
                                            cout << "Median of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_median(arr2d, row, i);
                                            cout << "Median of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '4')
                            {
                                // Find Mean
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find Mean for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_mean(arr2d, row, index);
                                            cout << "Mean of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_mean(arr2d, row, i);
                                            cout << "Mean of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '5')
                            {
                                // Find Variance
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find Variance for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_variance(arr2d, row, index);
                                            cout << "Variance of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_variance(arr2d, row, i);
                                            cout << "Variance of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '6')
                            {
                                // Find Standard Deviation
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                cout << "       Computable Titles       " << endl;
                                cout << "+---------+-------------------+" << endl;
                                cout << "|  Index  |       Titles      |" << endl;
                                cout << "+---------+-------------------+" << endl;
                                for (int i = 0; i < titles.size(); i++)
                                {
                                    if (computable[i] == 1)
                                    {
                                        cout << "|" << setw(5) << titles[i].second << setw(5)
                                             << "|" << setw(13) << titles[i].first << setw(7)
                                             << "|" << endl;
                                    }
                                }
                                cout << "+---------+-------------------+" << endl;

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find STDV for single column
                                    while (true)
                                    {
                                        cout << "Select title by index" << endl;
                                        int choice;
                                        cin >> choice;
                                        ;
                                        int index = choice - 1;

                                        if (computable[index] == 0)
                                        {
                                            cout << "Error: Title not computable" << endl;
                                            pressEnter();
                                        }
                                        else if (choice < 0 || choice > computable.size())
                                        {
                                            cout << "Error: Invalid index" << endl;
                                            pressEnter();
                                        }
                                        else
                                        {
                                            int min = find_stdv(arr2d, row, index);
                                            cout << "Standard Deviation of "
                                                 << titles[index].first << ": "
                                                 << min << endl;

                                            cin.ignore();
                                            pressEnter();
                                            break;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    for (int i = 0; i < titles.size(); i++)
                                    {
                                        if (computable[i] == 1)
                                        {
                                            int min = find_stdv(arr2d, row, i);
                                            cout << "Standard Deviation of "
                                                 << titles[i].first << ": "
                                                 << min << endl;
                                        }
                                    }
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
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
                        f.loadScreen();
                        int col = f.getCol();
                        int row = f.getRow();

                        // ------------------------------------------------------------------------------

                        vecpair titles = f.getTitle();
                        vector<int> computable = f.getCompute();
                        vector2d arr2d = f.getData();
                        cout << "       Computable Titles       " << endl;
                        cout << "+---------+-------------------+" << endl;
                        cout << "|  Index  |       Titles      |" << endl;
                        cout << "+---------+-------------------+" << endl;
                        for (int i = 0; i < titles.size(); i++)
                        {
                            if (computable[i] == 1)
                            {
                                cout << "|" << setw(5) << titles[i].second << setw(5)
                                     << "|" << setw(13) << titles[i].first << setw(7)
                                     << "|" << endl;
                            }
                        }
                        cout << "+---------+-------------------+" << endl;

                        // Find STDV for single column
                        while (true)
                        {
                            cout << "Select title by index" << endl;
                            int choice;
                            cin >> choice;
                            int index = choice - 1;

                            if (computable[index] == 0)
                            {
                                cout << "Error: Title not computable" << endl;
                                pressEnter();
                            }
                            else if (choice < 0 || choice > computable.size())
                            {
                                cout << "Error: Invalid index" << endl;
                                pressEnter();
                            }
                            else
                            {
                                int min = find_min(arr2d, row, index);
                                int max = find_max(arr2d, row, index);

                                // int min = find_stdv(arr2d, row, index);
                                // cout << "Standard Deviation of "
                                //      << titles[index].first << ": "
                                //      << min << endl;
                                string graph = histogram(arr2d, min, max, row, index);
                                cin.ignore();
                                pressEnter();
                                string s = Save_Report_Menu();
                                if (s == "1")
                                {
                                    // plain text
                                    f.saveTxtReport(graph);
                                }
                                else if (s == "2")
                                {
                                    // html
                                    string d = Generate_HTML_Report(graph);
                                    f.saveHtmlReport(d);
                                }

                                // f.htmlReportScreen();
                                break;
                            }
                        }
                    }

                    else if (choice == '3')
                    {
                        //Correlation
                        f.loadScreen();
                        int col = f.getCol();
                        int row = f.getRow();

                        // ------------------------------------------------------------------------------

                        vecpair titles = f.getTitle();
                        vector<int> computable = f.getCompute();
                        vector2d arr2d = f.getData();
                        cout << "       Computable Titles       " << endl;
                        cout << "+---------+-------------------+" << endl;
                        cout << "|  Index  |       Titles      |" << endl;
                        cout << "+---------+-------------------+" << endl;
                        for (int i = 0; i < titles.size(); i++)
                        {
                            if (computable[i] == 1)
                            {
                                cout << "|" << setw(5) << titles[i].second << setw(5)
                                     << "|" << setw(13) << titles[i].first << setw(7)
                                     << "|" << endl;
                            }
                        }
                        cout << "+---------+-------------------+" << endl;

                        // Find STDV for single column
                        while (true)
                        {
                            cout << "Select first title by index" << endl;
                            int choice1, choice2;
                            cin >> choice1;
                            int index1 = choice1 - 1;

                            cout << "Select second title by index" << endl;
                            cin >> choice2;
                            int index2 = choice2 - 1;

                            if (computable[index1] == 0 || computable[index2] == 0)
                            {
                                cout << "Error: Title not computable" << endl;
                                pressEnter();
                            }
                            else if (choice1 < 0 || choice2 < 0 || choice1 > computable.size() || choice2 > computable.size())
                            {
                                cout << "Error: Invalid index" << endl;
                                pressEnter();
                            }
                            else
                            {
                                // int min = find_min(arr2d, row, index);
                                // int max = find_max(arr2d, row, index);

                                // int min = find_stdv(arr2d, row, index);
                                // cout << "Standard Deviation of "
                                //      << titles[index].first << ": "
                                //      << min << endl;
                                // histogram(arr2d, min, max, row, index);
                                cin.ignore();
                                pressEnter();
                                Save_Report_Menu();

                                // f.htmlReportScreen();
                                break;
                            }
                        }
                    }
                    else if (choice == '4')
                    {
                        f.loadScreen();
                        int col = f.getCol();
                        int row = f.getRow();

                        // ------------------------------------------------------------------------------

                        vecpair titles = f.getTitle();
                        vector<int> computable = f.getCompute();
                        vector2d arr2d = f.getData();
                        cout << "       Computable Titles       " << endl;
                        cout << "+---------+-------------------+" << endl;
                        cout << "|  Index  |       Titles      |" << endl;
                        cout << "+---------+-------------------+" << endl;
                        for (int i = 0; i < titles.size(); i++)
                        {
                            if (computable[i] == 1)
                            {
                                cout << "|" << setw(5) << titles[i].second << setw(5)
                                     << "|" << setw(13) << titles[i].first << setw(7)
                                     << "|" << endl;
                            }
                        }
                        cout << "+---------+-------------------+" << endl;

                        // Find STDV for single column
                        while (true)
                        {
                            cout << "Select title by index" << endl;
                            int choice;
                            cin >> choice;
                            int index = choice - 1;

                            if (computable[index] == 0)
                            {
                                cout << "Error: Title not computable" << endl;
                                pressEnter();
                            }
                            else if (choice < 0 || choice > computable.size())
                            {
                                cout << "Error: Invalid index" << endl;
                                pressEnter();
                            }
                            else
                            {
                                int min = find_min(arr2d, row, index);
                                int max = find_max(arr2d, row, index);

                                vector<pair<int, int>> distinct = distinctMember(arr2d, index);
                                string form = tabularForm(distinct);

                                cin.ignore();
                                pressEnter();
                                Save_Report_Menu();

                                break;
                            }
                        }
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
                char input = Report_Menu();
                if (input == '1')
                {
                    f.txtReportScreen();
                }
                else
                {
                    f.htmlReportScreen();
                }
            }
            else if (choice == '3')
            {
                //View User log
                //f.showLogScreen();
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
