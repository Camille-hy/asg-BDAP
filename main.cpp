#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void Main_Menu(string name);
void Statistical_Analysis_Menu();
void Admin_Menu(string name);
void Report_Menu();
void Statistical_Calculation_Menu();

class Users {
public:
  string user;
  string pass;
  int status;
  int type;
};

void Menu_Dashboard() {
  system("cls");
  cout << "+--------------------------------------------------+" << endl;
  cout << "|            Basic Data Analysis Program           |" << endl;
  cout << "|                    (  BDAP  )                    |" << endl;
  cout << "+--------------------------------------------------+" << endl
       << endl;
}

bool checkUser(vector<Users> &users, string name, string pass) {
  bool found = false;
  for (auto elem : users) {
    if (name == elem.user && pass == elem.pass && elem.status == 1) {
      cout << elem.type << endl;
      found = true;
      break;
    }
  }
  return found;
}

bool checkType(vector<Users> &users, string name, string pass) {
  bool isAdmin = false;
  for (auto elem : users) {
    if (name == elem.user && pass == elem.pass && elem.status == 1 &&
        elem.type == 1) {
      cout << elem.type << endl;
      isAdmin = true;
      break;
    }
  }
  return isAdmin;
}

void User_Data_In(string usertype, string username, string password) {
  int admin = 1, active = 1;
  int user = 0;
  ofstream file;
  file.open("UserData.txt", fstream::app);

  if (usertype == "Admin" || usertype == "admin") {
    file << username << " " << password << " " << active << " " << admin
         << endl;
  } else if (usertype == "User" || usertype == "user") {
    file << username << " " << password << " " << active << " " << user << endl;
  }
  file.close();
}

bool check_pw(string password) {
  bool hasUpper = false, hasDigit = false;
  for (int i = 0; i < password.length(); i++) {
    if (isupper(password[i]))
      hasUpper = true;
    else if (isdigit(password[i]))
      hasDigit = true;
  }
  if (hasUpper && hasDigit)
    return true;
  else
    return false;
}

void UserRegister() {
  string usertype, username, password, confirmpw;
  bool valid;

  do {
    cout << "User Type(Admin/User): ";
    cin >> usertype;
    cin.ignore(80, '\n');
    cout << "Username: ";
    cin >> username;
    cin.ignore(80, '\n');
    cout << "Password: ";
    cin >> password;
    cin.ignore(80, '\n');
    cout << "Confirm Password: ";
    cin >> confirmpw;
    cin.ignore(80, '\n');

    if (usertype != "Admin" && usertype != "admin" && usertype != "User" &&
        usertype != "user")
      cout << "User type does not exist" << endl;
    else if (confirmpw != password)
      cout << "Password does not match" << endl;
    else if (!isalpha(password[0]))
      cout << "Password can only start with letter" << endl;
    else if (check_pw(password)) {
      User_Data_In(usertype, username, password);
      valid = true;
    } else
      cout << "Password must include at least one capital letter and one digit!"
           << endl;
  } while (!valid);
}

int main() {
  bool found = false;
  bool isAdmin = false;
  char choice;
  cout << "+--------------------------------------------------+" << endl;
  cout << "|                    Welcome to                    |" << endl;
  cout << "|            Basic Data Analysis Program           |" << endl;
  cout << "|                    (  BDAP  )                    |" << endl;
  cout << "+--------------------------------------------------+" << endl;
  cout << endl;
  do {
    cout << "Please Choose " << endl << endl;
    cout << "1. Login" << endl;
    cout << "2. Quit" << endl;
    cin >> choice;
    if (choice == '1') {
      Users userdata;
      vector<Users> users;
      ifstream file;
      file.open("UserData.txt");
      while (file >> userdata.user) {
        file >> userdata.pass;
        file >> userdata.status;
        file >> userdata.type;
        users.push_back(userdata);
      }
      file.close();
      string name, pass;

      do {
        cout << "Please enter username: ";
        cin >> name;
        cout << "Please enter password: ";
        cin >> pass;
        isAdmin = checkType(users, name, pass);
        if (isAdmin) {
          Admin_Menu(name);
        } else {
          Main_Menu(name);
        }

      } while (!checkUser(users, name, pass));

    } else if (choice == '2') {
      cout << "See ya!" << endl;
      break;
    } else
      cout << "Invalid choice " << endl;

  } while (choice != '1' && choice != '2');

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
    cin >> user_choice;

    if (user_choice == '1') {
      cout << "Minimum" << endl;
    }

    else if (user_choice == '2') {
      cout << "Maximum" << endl;
    }

    else if (user_choice == '3') {
      cout << "Mediank" << endl;
    }

    else if (user_choice == '4') {
      cout << "Meank" << endl;
    }

    else if (user_choice == '5') {
      cout << "Varaince" << endl;
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
    cin >> user_choice;

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

void Report_Menu() {
  bool valid;
  char user_choice;

  cout << "1.   View plain text report" << endl;
  cout << "2.   View HTML report" << endl;

  while (valid) {
    cout << "Please Enter Your choice: ";
    cin >> user_choice;

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

void Admin_Menu(string name) {
  bool valid;
  char user_choice;
  cout << "1.   Create User Account" << endl;
  cout << "2.   Modify User Account" << endl;
  cout << "3.   Log out" << endl;

  cout << "Welcome Admin," << name << endl << endl;
  while (valid) {
    cout << "Please Enter Your choice: ";
    cin >> user_choice;

    if (user_choice == '1') {
      cout << "Create User Account" << endl;
    }

    else if (user_choice == '2') {
      cout << "Modify User Account" << endl;
    }

    else if (user_choice == '3') {
      cout << "Log out" << endl;
    }

    else {
      cout << "Invalid Input" << endl;
    }
  }
}