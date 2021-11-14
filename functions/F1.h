/* 
    All Functions in F1.h are implemented by 
    Student: CHUA HUI YI (1201100840)
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "misc.h"

using namespace std;

#if defined(__linux__) || defined(__APPLE__)
    #define mkdir "mkdir -p "
    #define slash "/"
#else
    #define mkdir "mkdir "
    #define slash "\\"
#endif

// Class for User Account
class Users {
    public:
        string user;
        string pass;
        int status;
        int type;
};

/* ========================================================== */

// Append new user to file
// In: User Type, Username, Password
// Out: Append data to file
// Effective lines: 12
void User_Data_In(string usertype, string username, string password)
{
    int admin=1, active=1;
    int user=0;
    ofstream file;
    file.open("UserData.txt", fstream::app);    // Open the file in append mode
    
    if (usertype == "Admin" || usertype == "admin")
    {
        file << username << " " << password << " " << active << " " << admin << endl;
    } else if (usertype == "User" || usertype == "user"){
        file << username << " " << password << " " << active << " " << user << endl;
        string dir = "Users_Folder";
        string path = dir + slash + username;   // Create new folder for user
        system((mkdir + path).c_str());
    }
    file.close();

}

/* ========================================================== */

// Check if username and password correct, check user status and user type (admin or user)
// In: Vector(users), Username, Password, boolean isAdmin (pass by reference)
// Out: return found
// Effective lines: 12
bool checkUser(vector<Users> &users, string name, string pass, bool &isAdmin){
    bool found = false;     

    for (auto elem: users)      // range loop to loop through the vector to get the data
    {
        if (name == elem.user &&
            pass == elem.pass &&
            elem.status == 1)
        {
            found = true;   // Username and password are correct and the status is active
            if (elem.type == 1) {
                isAdmin = true;
            } else {
                isAdmin = false;
            }
            break;  // break the loop when user is found
        }
    }
    
    return found;
}


// Check if registering account password is legit (at least 1 uppercase and 1 digit)
// In: Password
// Out: return boolean
// Effective lines: 8
bool check_Pw(string password)
{
    bool hasUpper = false, hasDigit = false;    // boolean variables to check if digit and uppercase letter are found
    for (int i = 0; i < password.length(); i++)
    {
        if(isupper(password[i])) hasUpper = true;
        else if(isdigit(password[i])) hasDigit = true;
    }
    if(hasUpper && hasDigit)
        return true;    // return true if both conditions are satisfied
    else
        return false;   // else return false
}


// Check if username or password has space
// In: Username, Password 
// Out: return hasSpace
// Effective lines: 8
bool check_Space(string username, string password)
{
    bool hasSpace = false;      // boolean variable to check if username and password have space

    for (int i = 0; i < username.size(); i++)
    {
        if(isspace(username[i]))
            hasSpace = true;
    }

    for (int i = 0; i < password.size(); i++)
    {
        if(isspace(password[i]))
            hasSpace = true;
    }
    return hasSpace;
}

/* ========================================================== */

// Read user account from file into a vector
// Using class (user defined datatype)
// Effective lines: 10
vector<Users> readUser() {
    ifstream file("UserData.txt");
    vector<Users> users;
    Users user;
    
    while(file >> user.user) {
        file >> user.pass;
        file >> user.status;
        file >> user.type;
        users.push_back(user);      // append data to vector users
    }

    file.close();
    return users;
}


// Find the user account info in the vector and return its index
// In: Vector(users), Username
// Out: return index
// Effective lines: 4
int findUserbyName(vector<Users> users, string name) {
    for (int i=0;i<users.size();i++) {

        if (users[i].user == name && users[i].status == 1) {
            return i;   
        }
    }
    return -1;  // return -1 if user is not found in database
}


// Delete User Account 
// In: Vector(users), Index
// Out: Change status to 0
// Effective lines: 1
void deleteUser(vector<Users> &users, int index) {
    users[index].status = 0;    
}


// Change User Account password
// In: Vector(users), Index, Password
// Out: Change user password
// Effective lines: 1
void modifyUser(vector<Users> &users, int index, string password) {
    users[index].pass = password;
}


// Rewrite whole user account data in file after deleting or changing password
// In: Vector(users)
// Out: Rewrite data file
// Effective lines: 6
void writeUser(vector<Users> users) {
    ofstream file("UserData.txt");
    for (int i=0;i<users.size();i++) {
        file << users[i].user << " " << users[i].pass << " " << users[i].status << " " << users[i].type;
        if (i != users.size()) {
            file << endl;   // an empty line at the end of the file
        }
    }
    file.close();
}

/* ========================================================== */

// Check username and password from user input
// In: User Type, Username, Password, ConfirmPassword, Valid
// Out: -
// Effective lines: 26
void checkInformation(string usertype, string username, string password, string confirmPw, bool &valid)
{
    bool usernameExist = false;     // check if the username exists in database
    vector<Users> users = readUser();
    for (auto elem: users)
    {
        if (username == elem.user && elem.status == 1){
            usernameExist = true;   // username is found in database
        }
    }
    
    if(usertype != "Admin" && usertype != "admin" && usertype != "User" && usertype != "user")
        cout << "User type does not exist" << endl;
    else if (usernameExist)
        cout << "Username already exists" << endl;
    else if (check_Space(username, password))
        cout << "Username and password cant consist of spaces" << endl;
    else if(username.size() > 20)
        cout << "Username cant be more than 20 characters" << endl;
    else if (password.size() > 20)
        cout << "Password cant be more than 20 characters" << endl;
    else if (password != confirmPw)
        cout << "Password does not match" << endl;
    else if(!isalpha(password[0]))  // Check if password starts with a letter
        cout << "Password can only start with letter" << endl;
    else if(check_Pw(password)){
        User_Data_In(usertype, username, password);     // Call function to write in the data if username and password are legit
        cout << "Register successful" << endl;
        valid = true;   // Break the loop
    }
    else
        cout << "Password must include at least one capital letter and one digit!" << endl;
        pressEnter();
}


// Registering User Account
// In: -
// Out: -
// Effective lines: 17
void UserRegister()
{
    string usertype, username, password, confirmPw;
    bool valid = false;
    
    do{
        clearScreen();
        cout << "Register User Account" << endl << endl;
        cout << "User Type(Admin/User): " ; 
        cin >> usertype; 
        cin.ignore(80, '\n');
        cout << "Username: " ; 
        getline(cin, username); 
        cout << "Password: " ; 
        getline(cin, password); 
        cout << "Confirm Password: " ; 
        cin >> confirmPw;
        cin.ignore(80, '\n');

        checkInformation(usertype, username, password, confirmPw, valid);
    }while(!valid);

}

/* ========================================================== */

// Show all Users information
// In: -
// Out: -
// Effective lines: 10
void UserInfo()
{
    clearScreen();
    cout << "Delete User Account" << endl << endl;
    cout << "Status 0 = Deleted, Status 1 = Active" << endl;
    cout << "Type 0 = User, Type 1 = Admin" << endl << endl;
    vector<Users> users = readUser();

    // Print the user data out
    for (Users u: users) {
        cout << "Username: " << left << setw(20) << fixed  << u.user << " " 
        << "Password: " << left << setw(20) << fixed  << u.pass << " " 
        << "Status: " <<  left << setw(20) << fixed  << u.status << " " 
        << "Type: " <<  left << setw(20) << fixed  << u.type << " " << endl;
    }
}


// Delete User Account
// In: -
// Out: - 
// Effective lines: 21
void UserDelete()
{
    bool userExists = false;    // check if user exists in database
    string username;
    vector<Users> users = readUser();
    UserInfo();
    cout << "\nPress enter to go back" << endl << endl;
    cin.ignore(80, '\n');
    do{
        
        cout << "Please enter the account username you wish to delete: " << endl;
        
        getline(cin, username);
        if(username == "")
        {
            userExists = true;
        }

        int index = findUserbyName(users, username);
        if(index == -1)     // If index is -1, the user is not found
        {
            cout << "User does not exists or is deleted" << endl;
        }
        else{
            deleteUser(users, index);
            writeUser(users);
            cout << "User deleted" << endl;
            pressEnter();
            userExists = true;
        }
    }while(!userExists);

}


// Check if password is valid
// In: Valid, Username, Password
// Out: -
// Effective lines: 14
void passwordValidation(bool &valid, string username, string newpass)
{
    vector<Users> users = readUser();
    int index = findUserbyName(users, username);
    cout << "Enter new password: ";
    cin >> newpass; cin.ignore(80, '\n');
    if(!isalpha(newpass[0]))
        cout << "Password can only start with letter" << endl;
    else if(check_Pw(newpass)){
        modifyUser(users, index, newpass);
        writeUser(users);
        cout << "Password Changed" << endl;
        pressEnter();
        valid = true;
    }
    else{
        cout << "Password must include at least one capital letter and one digit!" << endl;
    }
}


// Menu for Change User Password (Admin)
// In: -
// Out: -
// Effective lines: 20
void AdminChangePassword()
{
    bool userExists = false, valid = false;
    string username, newpass;
    vector<Users> users = readUser();
    UserInfo();

    cout << "\nPress enter to go back" << endl << endl;
    cin.ignore(80, '\n');
    do{
        cout << "Please enter the account username you wish to change password: " << endl;
        getline(cin, username);
        
        if(username == "")
        {
            userExists = true;
        }

        int index = findUserbyName(users, username);
        if(index == -1){
            cout << "User does not exists or is deleted" << endl;
        }
        else{
            userExists = true;
            do{
                passwordValidation(valid, username, newpass);
            }while(!valid);
        }
    }while(!userExists);
}


// Change User Password (User)
// In: Username
// Out: -
// Effective lines: 21
void UserChangePassword(string username){
    bool valid = false;
    string newpass;
    cout << "\nPress enter to go back" << endl << endl;
    do{
        cout << "Enter new password: ";
        getline(cin, newpass);
        if(newpass == "")
        {
            valid = true;
        }
        vector<Users> users = readUser();
        int index = findUserbyName(users, username);
        if(!isalpha(newpass[0]))
            cout << "Password can only start with letter" << endl;
        else if(check_Pw(newpass)){
            modifyUser(users, index, newpass);
            writeUser(users);
            cout << "Password Changed" << endl;
            pressEnter();
            valid = true;
        }
        else{
            cout << "Password must include at least one capital letter and one digit!" << endl;
        }
    }while(!valid);

}

/* ========================================================== */

// Screen
// In: Username, Password
// Out: -
// Effective lines: 11
void dashboard(string &name, string &pass)
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl << endl;
    cout << "Please enter username: ";
    cin >> name;
    cout << "Please enter password: ";
    cin >> pass;
    cout << endl;
}


// Login Menu
// In: Stat(flag), isAdmin, Username
// Out: -
// Effective lines: 27
int Login_Choice(char &stat, bool &isAdmin, string &name)
{
    char choice;
    cout << "Please Choose -" << endl << endl;
    cout << "1. Login" << endl;
    cout << "2. Quit" << endl << endl;
    cout << "Please Enter your choice: ";
    cin >> choice;

    if (choice == '1')
    {
        stat = false;
        // Proceed to Login Menu

        // use readUser() to get users list from UserData.txt
        vector<Users> users = readUser();
        string pass;

        do
        {
            dashboard(name, pass);
            bool found;
            found = checkUser(users, name, pass, isAdmin);

            if (!found) // if username or password is wrong or not found in database
            {
                cout << "Your username or password is incorrect" << endl;
                cout << "Press enter to continue" << endl;
                cin.ignore(30, '\n');
                cin.get();
            }

        } while (!checkUser(users, name, pass, isAdmin));
    }
    else if (choice == '2')
    {
        stat = false;
        // Exit Program
        cout << "Exiting Program..." << endl;
        exit(0);
    }
    else
    {
        stat = true;
    }
    return 0;
}
