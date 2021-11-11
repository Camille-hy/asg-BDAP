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
        while (true)
        {
            Admin_Menu(name);
            choice = Admin_Menu_Selection(name);
            while (choice != '1' && choice != '2' && choice != '3') // Bool remain true until user entered valid selection
            {
                Admin_Menu(name);
                cout << "Invalid Input" << endl;
                choice = Admin_Menu_Selection(name);
            }

            if (choice == '1')
            {
                UserRegister();
            }
            else if (choice == '2')
            {
                while (true)
                {
                    Modify_User_Menu();
                    choice = Modify_User_Selection();
                    while (choice != '1' && choice != '2' && choice != '3')
                    {
                        Modify_User_Menu();
                        cout << "Invalid Choice" << endl;
                        choice = Modify_User_Selection();
                    }
                    if (choice == '1')
                    {
                        AdminChangePassword();
                    }
                    else if (choice == '2')
                    {
                        UserDelete();
                    }
                    else if (choice == '3')
                    {
                        break;
                    }
                }
            }
            else if (choice == '3')
            {
                cout << "Logging Out..." << endl;
                pressEnter();
                main();
                break;
            }
        }
    }
    else
    {
        Logger logger(name);
        File f(name);
        while (true) // Remain in User Menu
        {
            User_Menu(name);
            choice = User_Menu_Selection(name);
            cin.ignore(50, '\n');
            cin.get();

            while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') // Bool remain true until user entered valid selection
            {
                User_Menu(name);
                cout << "Invalid Input" << endl;
                logger.log("User Enter Invalid Input");
                choice = User_Menu_Selection(name);
            }
            cout << choice << endl;
            if (choice == '1') // Statistical Analysis Menu
            {
                logger.log("User enter statistical analysis menu");
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
                    int result = -1;
                    string method;

                    if (choice == '1')
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
                            // Find Minimum
                            if (choice == '1')
                            {
                                logger.log("User chooses minimum");
                                method = "MINIMUM";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find for single column
                                    logger.log("User chooses to find single column");
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {

                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {

                                                // html
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    logger.log("User chooses to find all column");
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }

                            else if (choice == '2')
                            {
                                // Find Maximum
                                logger.log("User chooses maximum");
                                method = "MAXIMUM";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    logger.log("User chooses to find single column");
                                    // Find for single column
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {
                                                // plain text
                                                logger.log("User save plain text report");
                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {
                                                // html
                                                logger.log("User save html report");
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '3')
                            {
                                logger.log("User chooses median");
                                // Find Median
                                method = "MEDIAN";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find for single column
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {
                                                // plain text
                                                logger.log("User save plain text report");
                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {
                                                // html
                                                logger.log("User save html report");
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '4')
                            {
                                // Find Mean
                                logger.log("User chooses mean");
                                method = "MEAN";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find for single column
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {
                                                // plain text
                                                logger.log("User save plain text report");
                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {
                                                // html
                                                logger.log("User save html report");
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '5')
                            {
                                logger.log("User chooses variance");
                                // Find Variance
                                method = "VARIANCE";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find for single column
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {
                                                // plain text
                                                logger.log("User save plain text report");

                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {
                                                // html
                                                logger.log("User save html report");
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
                                    cin.ignore();
                                    pressEnter();
                                    break;
                                }
                            }
                            else if (choice == '6')
                            {
                                // Find Standard Deviation
                                logger.log("User chooses standard deviation");
                                method = "STANDARD DEVIATION";
                                f.loadScreen();
                                int col = f.getCol();
                                int row = f.getRow();
                                vecpair titles = f.getTitle();
                                vector<int> computable = f.getCompute();
                                vector2d arr2d = f.getData();
                                showComputableTitles(titles, computable);

                                int select_col = select_column();

                                while (select_col != '1' && select_col != '2') // bool remain true until user entered valid selection
                                {
                                    cout << "Invalid Input" << endl;
                                    select_col = select_column();
                                }

                                if (select_col == '1')
                                {
                                    // Find for single column
                                    flag = true;
                                    bool flag2 = false;
                                    while (flag)
                                    {
                                        result = singleColumnCompute(method, choice, titles, computable, arr2d, row, flag2);
                                        if (flag2)
                                        {
                                            string s = Save_Report_Menu();
                                            string d;
                                            int choicetoint = choice - '0';
                                            int index = choicetoint - 1;

                                            if (s == "1")
                                            {
                                                // plain text
                                                logger.log("User save plain text report");
                                                d = Generate_Plain_Text_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }
                                            else if (s == "2")
                                            {
                                                // html
                                                d = Generate_HTML_Report(method, to_string(result), titles[index].first);
                                                f.saveHtmlReport(d);
                                            }

                                            flag = false;
                                        }
                                    }
                                }
                                else if (select_col == '2')
                                {
                                    // Find for all column
                                    allColumnCompute(method, titles, computable, choice, arr2d, row);
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

                        logger.log("User chooses histogram");
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
                                    string d = Generate_Plain_Text_Report("HISTOGRAM", graph, titles[index].first);
                                    f.saveTxtReport(d);
                                }
                                else if (s == "2")
                                {
                                    // html
                                    string d = Generate_HTML_Report("HISTOGRAM", graph, titles[index].first);
                                    f.saveHtmlReport(d);
                                }

                                break;
                            }
                        }
                    }

                    else if (choice == '3')
                    {
                        logger.log("User chooses correlation");
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
                                double c = correlation(arr2d, row, index1, index2);
                                cout << "Correlation of "
                                     << titles[index1].first << " & " << titles[index2].first << ": "
                                     << c << endl;

                                /// ---------------------------------------------------------
                                cin.ignore();
                                pressEnter();

                                string s = Save_Report_Menu();
                                if (s == "1")
                                {
                                    // plain text
                                    string d = Generate_Plain_Text_Report("CORRELATION", to_string(c), titles[index1].first, titles[index2].first);
                                    f.saveTxtReport(d);
                                }
                                else if (s == "2")
                                {
                                    // html
                                    string d = Generate_HTML_Report("CORRELATION", to_string(c), titles[index1].first, titles[index2].first);
                                    f.saveHtmlReport(d);
                                }

                                break;
                            }
                        }
                    }
                    else if (choice == '4')
                    {
                                                                    logger.log("User chooses distinct me");
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
                                // int min = find_min(arr2d, row, index);
                                // int max = find_max(arr2d, row, index);

                                vector<pair<int, int>> distinct = distinctMember(arr2d, index);
                                string form = tabularForm(distinct);

                                cin.ignore();
                                pressEnter();
                                // Save_Report_Menu();
                                string s = Save_Report_Menu();
                                if (s == "1")
                                {
                                    // plain text
                                    string d = Generate_Plain_Text_Report("DISTINCT DATA MEMBERS", form, titles[index].first);
                                    f.saveTxtReport(d);
                                }
                                else if (s == "2")
                                {
                                    // html
                                    string d = Generate_HTML_Report("DISTINCT DATA MEMBERS", form, titles[index].first);
                                    f.saveHtmlReport(d);
                                }
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
                logger.log("User view saved report");
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
                logger.log("User view user log");
                logger.showLogScreen();
            }
            else if (choice == '4')
            {
                // Change Password
                logger.log("User change password");
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
