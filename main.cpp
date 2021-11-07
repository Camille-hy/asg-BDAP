#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


#if defined(__linux__) || defined(__APPLE__)
#define cls "clear"
#define mkdir "mkdir -p "
#define slash "/"
#else
#define cls "cls"
#define mkdir "mkdir "
#define slash "\\"
#endif

using namespace std;
// system((mkdir+ "Users_Folder"))

void clearScreen() {
    system(cls);
}

class Users {
public:
    string user;
    string pass;
    int status;
    int type;
};

string global_username;
void Main_Menu(string name);
void Statistical_Analysis_Menu();
void Admin_Menu(string name = global_username);
void Report_Menu();
void Statistical_Calculation_Menu();
void Modify_User_Account();
vector<Users> readUser();
void UserDelete();
void ChangePassword();
void Generate_HTML_Report();

void pressEnter(){
    cout << "Press enter to continue" << endl;
    cin.get();
}

void Menu_Dashboard()
{
    system("cls");
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}

void Login_Screen() {
    system("cls");
    readUser();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                    Welcome to                    |" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;    
}

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
    }
    file.close();
}

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

void UserRegister()
{
    string usertype, username, password, confirmpw;
    bool valid = false;
    
    do{
        Menu_Dashboard();
        cout << "Register User Account" << endl << endl;
        cout << "User Type(Admin/User): " ; cin >> usertype; cin.ignore(80, '\n');
        cout << "Username: " ; cin >> username; cin.ignore(80, '\n');
        cout << "Password: " ; cin >> password; cin.ignore(80, '\n');
        cout << "Confirm Password: "; cin >> confirmpw; cin.ignore(80, '\n');

        if(usertype != "Admin" && usertype != "admin" && usertype != "User" && usertype != "user")
            cout << "User type does not exist" << endl;
        else if(confirmpw != password)
            cout << "Password does not match" << endl;
        else if(!isalpha(password[0]))
            cout << "Password can only start with letter" << endl;
        else if(check_pw(password)){
            User_Data_In(usertype, username, password);
            cout << "Register successful" << endl;
            string dir = "Users_Folder";
            string path = dir + slash + username;
            system((mkdir + path).c_str());
            valid = true;
        }
        else
            cout << "Password must include at least one capital letter and one digit!" << endl;
            cout << "Press enter to continue" << endl;
            cin.get();
    }while(!valid);

    Admin_Menu();

}




void Generate_HTML_Report(){
    
}


// void distinctMember(vector<vector<int>> data, int col) {
//     vector<int> distincts;
//     for (auto row: data) {
//         for (auto col: row) {
//             if (find(distincts.begin(), distincts.end(), col) != distincts.end()) {
//                 distincts.push_back(col);
//             }
//         }
//     }
// }






int main()
{
    system("cls");
    bool found = false;
    bool isAdmin = false;
    char choice;
    Login_Screen();
    cout << "Please Choose " << endl << endl;
    cout << "1. Login" << endl;
    cout << "2. Quit" << endl << endl;
    do{
        cout << "Please Enter Your choice: ";
        cin >> choice; cin.ignore(80, '\n');
        if(choice == '1')
        {
            Users userdata;
            vector<Users> users;
            ifstream file;
            file.open("UserData.txt");
            while (file>>userdata.user)
            {
                file>>userdata.pass;
                file>>userdata.status;
                file>>userdata.type;
                users.push_back(userdata);
            }
            file.close();
            string name, pass;
            
            // bool isAdmin;
            do{
                Menu_Dashboard();
                cout << endl << endl;
                cout<< "Please enter username: " ;
                cin >> name;
                cout<< "Please enter password: " ;
                cin >> pass;
                system("cls");
                bool isAdmin;
                bool found;
                found = checkUser(users, name, pass, isAdmin);
                // isAdmin = checkType(users, name, pass);
                if (found) {
                    global_username = name;
                    // File file(name);     // cz function
                    // Logger logger(name); //cz function

                    if(isAdmin){
                        Admin_Menu();
                    } else {
                        Main_Menu(name);
                    }
                } else {
                    cout << "Your username or password is incorrect" << endl;
                    cout << "Press enter to continue" << endl;
                    cin.ignore(30,'\n');
                    cin.get();
                }

            }while(!checkUser(users, name, pass, isAdmin));

        }else if(choice == '2'){
            cout << "See ya!" << endl;
            break;
        }else
            cout << "Invalid choice " << endl;

    }while(choice!='1' && choice!='2');

    return 0;
}


void Statistical_Analysis_Menu() {
    bool valid;
    char user_choice;
    Menu_Dashboard();
    cout << "1.   Statistical Calculation" << endl;
    cout << "2.   Plot Histogram" << endl;
    cout << "3.   Correlation" << endl;
    cout << "4.   Distinct data members" << endl;
    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice;
        if (user_choice == '1') {
        cout << "Statistical calculation" << endl;
        } else if (user_choice == '2') {
        cout << "Plot histogram" << endl;
        } else if (user_choice == '3') {
        cout << "Correlation" << endl;
        } else if (user_choice == '4') {
        cout << " Distinct data members" << endl;
        }
        else {
        cout << "Invalid Input" << endl;
        }
    }
}

void Statistical_Calculation_Menu() {
    bool valid;
    char user_choice;

    cout << "1.   Minimum" << endl;
    cout << "2.   Maximum" << endl;
    cout << "3.   Median" << endl;
    cout << "4.   Mean" << endl;
    cout << "5.   Variance" << endl;
    cout << "6.   Standard Deviation" << endl;

    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice; cin.ignore(30, '\n');

        if (user_choice == '1') {
        cout << "Minimum" << endl;
        }

        else if (user_choice == '2') {
        cout << "Maximum" << endl;
        }

        else if (user_choice == '3') {
        cout << "Median" << endl;
        }

        else if (user_choice == '4') {
        cout << "Mean" << endl;
        }

        else if (user_choice == '5') {
        cout << "Variance" << endl;
        }

        else if (user_choice == '5') {
        cout << "Standard Deviation" << endl;
        }

        else {
        cout << "Invalid Input" << endl;
        }
    }
}

void Main_Menu(string name) {
    bool valid;
    char user_choice;
    Menu_Dashboard();

    cout << "1.   Enter Statistical Analysis Menu" << endl;
    cout << "2.   View Saved Report" << endl;
    cout << "3.   View User Log" << endl;
    cout << "4.   Change Password" << endl;
    cout << "5.   Log out" << endl;
    cout << "Welcome User, " << name << endl << endl;

    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice; cin.ignore(30, '\n');

        if (user_choice == '1') {
        cout << "Statistical Menu" << endl;
        }

        else if (user_choice == '2') {
        cout << "Saved Report" << endl;
        }

        else if (user_choice == '3') {
        cout << "User log" << endl;
        }

        else if (user_choice == '4') {
        cout << " Change password" << endl;
        }

        else if (user_choice == '5') {
        cout << "Log out" << endl;
        }

        else {
        cout << "Invalid Input" << endl;
        }
    }
}


void Modify_User_Menu() {
    clearScreen();
    bool valid = true;
    char user_choice;
    Menu_Dashboard();
    cout << "1.   Change Password" << endl;
    cout << "2.   Delete User Account" << endl;
    cout << "3.   Back" << endl;

    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice; cin.ignore(30, '\n');

        if (user_choice == '1') {
            clearScreen();
            cout << "Change Password" << endl << endl;
            cout << "Status 0 = Deleted, Status 1 = Active" << endl;
            cout << "Type 0 = User, Type 1 = Admin" << endl << endl;
            ChangePassword();
            break;
        }
        else if (user_choice == '2') {
            clearScreen();
            cout << "Delete user account" << endl << endl;
            cout << "Status 0 = Deleted, Status 1 = Active" << endl;
            cout << "Type 0 = User, Type 1 = Admin" << endl << endl;
            UserDelete();
            break;
        }else if(user_choice == '3'){
            clearScreen();
            Admin_Menu();
            break;
        }

        else {
            cout << "Invalid Input" << endl;
        }
    }
}


void Report_Menu() {
    bool valid;
    char user_choice;

    cout << "1.   View plain text report" << endl;
    cout << "2.   View HTML report" << endl;

    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice; cin.ignore(30, '\n');

        if (user_choice == '1') {
        cout << "Plain Text Report" << endl;
        }

        else if (user_choice == '2') {
        cout << "HTML Report" << endl;
        }

        else {
        cout << "Invalid Input" << endl;
        }
    }
}


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

    // for (Users u: users) {
    //     cout << u.user << " " << u.pass << " " << u.status << " " << u.type << endl;
    // }
    file.close();
    return users;
}

int findUserbyName(vector<Users> users, string name) {
    for (int i=0;i<users.size();i++) {
        // cout << u.user << " " << u.pass << " " << u.status << " " << u.type << endl;
        if (users[i].user == name && users[i].status == 1) {
            return i;
        }
    }
    return -1;
}

void deleteUser(vector<Users> &users, int index) {
    users[index].status = 0;
}

void modifyUser(vector<Users> &users, int index, string password) {
    users[index].pass = password;
}

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

void Admin_Menu(string name) {
    bool valid = true;
    char user_choice;
    Menu_Dashboard();
    
    cout << "Welcome Admin," << name << endl << endl;
    cout << "1.   Create User Account" << endl;
    cout << "2.   Modify User Account" << endl;
    cout << "3.   Log out" << endl;

    while (valid) {
        cout << "Please Enter Your choice: ";
        cin >> user_choice; cin.ignore(30, '\n');

        if (user_choice == '1') {
            UserRegister(); 
            break;
        }

        else if (user_choice == '2') {
            cout << "Modify User Account" << endl;
            Modify_User_Menu();
            break;
        }

        else if (user_choice == '3') {
            main();
            break;
        }
        else {
        cout << "Invalid Input" << endl;
        }
    }
}

void UserDelete()
{
    bool userExists = false;
    string username;
    vector<Users> users = readUser();
    for (Users u: users) {
        cout << "Username: " << u.user << "\t\tPassword: " << " " << u.pass 
        << "\t\tStatus: " << u.status << " " 
        << "\t\tType: " << u.type << " " << endl;
    }
    
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
            Modify_User_Menu();
            userExists = true;
        }
    }while(!userExists);

}

void ChangePassword()
{
    bool userExists = false;
    bool valid = false;
    string username, newpass;
    vector<Users> users = readUser();
    for (Users u: users) 
        cout << "Username: " << u.user << "\t\tPassword: " << " " << u.pass << "\t\tStatus: " << u.status << " " << "\t\tType: " << u.type << " " << endl;
    
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
                    Modify_User_Menu();
                    valid = true;
                }
                else{
                    cout << "Password must include at least one capital letter and one digit!" << endl;
                }
            }while(!valid);
        }
    }while(!userExists);
}