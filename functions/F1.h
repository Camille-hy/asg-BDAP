#ifndef F1_H
#define F1_H

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
string global_username;


// Class for User Account
class Users {
    public:
        string user;
        string pass;
        int status;
        int type;
};



// Check if user status (is Admin or User)
bool checkUser(vector<Users> &users, string name, string pass, bool &isAdmin){
    bool found = false;

    for (auto elem: users)
    {
        if (name == elem.user &&
            pass == elem.pass &&
            elem.status == 1)
        {
            found = true;
            if (elem.type == 1) {
                isAdmin = true;
            } else {
                isAdmin = false;
            }
            break;
        }
    }
    
    return found;
}

// Append new user to file
void User_Data_In(string usertype, string username, string password)
{
    int admin=1, active=1;
    int user=0;
    ofstream file;
    file.open("UserData.txt", fstream::app);
    
    if (usertype == "Admin" || usertype == "admin"){
        file << username << " " << password << " " << active << " " << admin << endl;
    } else if (usertype == "User" || usertype == "user"){
        file << username << " " << password << " " << active << " " << user << endl;
        string dir = "Users_Folder";
        string path = dir + slash + username;
        system((mkdir + path).c_str());
    }
    file.close();

}

// Check if registering account password is legit
bool check_pw(string password)
{
    bool hasUpper = false, hasDigit = false;
    for (int i = 0; i < password.length(); i++)
    {
        if(isupper(password[i])) hasUpper = true;
        else if(isdigit(password[i])) hasDigit = true;
    }
    if(hasUpper && hasDigit)
        return true;
    else
        return false;
}

bool check_Space(string username, string password)
{
    bool hasSpace = false;

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

// Read user account from file into a vector
vector<Users> readUser() {
    ifstream file("UserData.txt");
    vector<Users> users;
    Users user;
    
    while(file >> user.user) {
        file >> user.pass;
        file >> user.status;
        file >> user.type;
        users.push_back(user);
    }

    file.close();
    return users;
}

// Find the user account info in the vector
int findUserbyName(vector<Users> users, string name) {
    for (int i=0;i<users.size();i++) {
        // cout << u.user << " " << u.pass << " " << u.status << " " << u.type << endl;
        if (users[i].user == name && users[i].status == 1) {
            return i;
        }
    }
    return -1;
}

// Delete User Account (Change status to 0)
void deleteUser(vector<Users> &users, int index) {
    users[index].status = 0;
}

// Change User Account password
void modifyUser(vector<Users> &users, int index, string password) {
    users[index].pass = password;
}

// Rewrite whole user account data in file after deleting or changing
void writeUser(vector<Users> users) {
    ofstream file("UserData.txt");
    for (int i=0;i<users.size();i++) {
        file << users[i].user << " " << users[i].pass << " " << users[i].status << " " << users[i].type;
        if (i != users.size()) {
            file << endl;
        }
    }
    file.close();
}

void checkInformation(string usertype, string username, string password, string confirmPw, bool &valid){
    bool usernameExist = false;
    vector<Users> users = readUser();
    for (auto elem: users)
    {
        if (username == elem.user && elem.status == 1){
            usernameExist = true;
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
    else if(!isalpha(password[0]))
        cout << "Password can only start with letter" << endl;
    else if(check_pw(password)){
        User_Data_In(usertype, username, password);
        cout << "Register successful" << endl;
        valid = true;
    }
    else
        cout << "Password must include at least one capital letter and one digit!" << endl;
        pressEnter();
}

// Registering User Account
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

// Show all Users information
void UserInfo(){
    clearScreen();
    cout << "Delete User Account" << endl << endl;
    cout << "Status 0 = Deleted, Status 1 = Active" << endl;
    cout << "Type 0 = User, Type 1 = Admin" << endl << endl;
    vector<Users> users = readUser();

    for (Users u: users) {
        cout << "Username: " << left << setw(20) << fixed  << u.user << " " 
        << "Password: " << left << setw(20) << fixed  << u.pass << " " 
        << "Status: " <<  left << setw(20) << fixed  << u.status << " " 
        << "Type: " <<  left << setw(20) << fixed  << u.type << " " << endl;
    }
}

// Menu for Delete User Account
void UserDelete()
{
    bool userExists = false;
    string username;
    vector<Users> users = readUser();
    UserInfo();
    
    do{
        cout << "\nPlease enter the account username you wish to delete: " << endl;
        cin >> username; cin.ignore(80, '\n');
        int index = findUserbyName(users, username);
        if(index == -1){
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

// Menu for Change User Password (Admin)
void AdminChangePassword()
{
    bool userExists = false, valid = false;
    string username, newpass;
    vector<Users> users = readUser();
    UserInfo();
    
    do{
        cout << "\nPlease enter the account username you wish to change password: " << endl;
        cin >> username; cin.ignore(80, '\n');
        int index = findUserbyName(users, username);
        if(index == -1){
            cout << "User does not exists or is deleted" << endl;
        }
        else{
            userExists = true;
            do{
                cout << "Enter new password: ";
                cin >> newpass; cin.ignore(80, '\n');
                if(!isalpha(newpass[0]))
                    cout << "Password can only start with letter" << endl;
                else if(check_pw(newpass)){
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
    }while(!userExists);
}

// Change User Password (User)
void UserChangePassword(string username){
    bool valid = false;
    string newpass;
    
    do{
        cout << "Enter new password: ";
        cin >> newpass; cin.ignore(80, '\n');
        vector<Users> users = readUser();
        int index = findUserbyName(users, username);
        if(!isalpha(newpass[0]))
            cout << "Password can only start with letter" << endl;
        else if(check_pw(newpass)){
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
                   
            do{
                clearScreen();
                cout << "+--------------------------------------------------+" << endl;
                cout << "|            Basic Data Analysis Program           |" << endl;
                cout << "|                    (  BDAP  )                    |" << endl;
                cout << "+--------------------------------------------------+" << endl;
                cout << endl << endl;
                cout << "Please enter username: " ;
                cin >> name;
                cout << "Please enter password: " ;
                cin >> pass;
                cout << endl;
   
                bool found;
                found = checkUser(users, name, pass, isAdmin);

                if (!found){
                    cout << "Your username or password is incorrect" << endl;
                    cout << "Press enter to continue" << endl;
                    cin.ignore(30,'\n');
                    cin.get();
                }

            }while(!checkUser(users, name, pass, isAdmin));

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


#endif // F1_H