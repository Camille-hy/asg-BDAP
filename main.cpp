#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

class Users {
public:
    string user;
    string pass;
    int status;
    int type;
};

void Menu_Dashboard()
{
    system("cls");
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}

bool checkUser(vector<Users> &users, string name, string pass){
    bool found = false;
    for (auto elem: users)
    {
        if (name == elem.user &&
            pass == elem.pass &&
            elem.status == 1 )
        {
            found = true;
            break;
        }
    }
    return found;
}

bool checkType(vector<Users> &users, string name, string pass){
    bool isAdmin = false;
    for (auto elem: users)
    {
        if (name == elem.user &&
            pass == elem.pass &&
            elem.status == 1 &&
            elem.type == 1)
        {
            isAdmin = true;
            break;
        }
    }
    
    return isAdmin;
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
    bool valid;
    system("cls");
    do{
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
            valid = true;
        }
        else
            cout << "Password must include at least one capital letter and one digit!" << endl;
    }while(!valid);
}

char adminMenu(){
    char option;

    cout << "Please Choose" << endl << endl;
    cout << "1. Create User Account" << endl;
    cout << "2. Modify User Account" << endl;
    cout << "3. Log Out" << endl << endl;
    cin >> option; cin.ignore(80, '\n');

    return option;
}

int main()
{
    system("cls");
    bool found = false;
    bool isAdmin = false;
    bool isLogin = false;
    char choice, option;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                    Welcome to                    |" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl;
    do{
        cout << "Please Choose " << endl << endl;
        cout << "1. Login" << endl;
        cout << "2. Quit" << endl;
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

            do{
                cout<< "Please enter username: " ;cin >> name;
                cout<< "Please enter password: " ;cin >> pass;
                system("cls");
                isAdmin = checkType(users, name, pass);
                if(isAdmin){
                    cout << "+--------------------------------------------------+" << endl;
                    cout << "|            Basic Data Analysis Program           |" << endl;
                    cout << "|                    (  BDAP  )                    |" << endl;
                    cout << "+--------------------------------------------------+" << endl << endl;
                    cout << "Welcome Admin, " << name << endl << endl;

                    option = adminMenu();
                    if(option == '1')
                    {
                        UserRegister();
                        cout << "Register Successful" << endl << endl;
                        system("cls");
                        adminMenu();
                    }
                    else if(option == '3'){
                        cout << "See ya!" << endl << endl;
                        main();
                    }

                }else
                {   
                    cout << "+--------------------------------------------------+" << endl;
                    cout << "|            Basic Data Analysis Program           |" << endl;
                    cout << "|                    (  BDAP  )                    |" << endl;
                    cout << "+--------------------------------------------------+" << endl << endl;
                    cout << "Welcome User, " << name << endl << endl;
                    cout << "Please Choose" << endl << endl;
                    cout << "1. Enter Statistical Analysis Menu" << endl;
                    cout << "2. View Saved Report" << endl;
                    cout << "3. View User Log" << endl;
                    cout << "4. Change Password" << endl;
                    cout << "5. Log Out" << endl << endl;
                }

            }while(!checkUser(users, name, pass));

        }else if(choice == '2'){
            cout << "See ya!" << endl;
            break;
        }else
            cout << "Invalid choice " << endl;

    }while(choice!='1' && choice!='2');

    return 0;
}