#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <utility>
#include <iomanip>
#include "misc.h"

#if defined(__linux__) || defined(__APPLE__)
#define slash "/"
#define mkdir "mkdir -p"
#else
#define slash "\\"
#define mkdir "mkdir "
#endif

using namespace std;

void showHeader()
{
    clearScreen();
    cout << "+--------------------------------------------------+" << endl;
    cout << "|            Basic Data Analysis Program           |" << endl;
    cout << "|                    (  BDAP  )                    |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << endl
         << endl;
}

typedef vector<vector<int>> vector2d;
typedef vector<pair<string, int>> vecpair;

class File
{
private:
    int numCol = 0, numRow = 0;
    vector2d data;
    vecpair title;
    vector<int> compute;
    ifstream inFile;
    bool error;
    string dir = "Users_Folder", dataDir, reportDir, htmlDir;

    // ------------------------------------------------------------------------

    // Read number of columns from the data file
    int readCol(ifstream &file)
    {
        int col;
        file >> col;
        if (!col)
        {
            cout << "Number of column is missing" << endl;

            error = true;
            pressEnter();
            return 0;
        }
        file.ignore(100, '\n');
        return col;
    }

    // Read titles from the data file
    vecpair readTitle(ifstream &file)
    {
        vecpair titles;
        pair<string, int> temp;
        stringstream ss;
        string line;
        getline(inFile, line);
        ss << line;
        string col;
        int index = 1;
        // while (stream >> col)
        while (getline(ss, col, ','))
        {
            temp = {col, index};
            titles.push_back(temp);
            index++;
        }

        if (titles.size() != numCol)
        {
            error = true;
            int difference = numCol - titles.size();
            cout << difference << " title " << (difference > 1 ? "are" : "is") << " missing" << endl;

            titles.clear();
            pressEnter();
        }
        return titles;
    }

    //Read computable from data file
    vector<int> readCompute(ifstream &file)
    {
        vector<int> computes;
        stringstream ss;
        string line;
        getline(inFile, line);
        ss << line;
        string col;
        // while (stream >> col)
        while (getline(ss, col, ','))
        {
            computes.push_back(stoi(col));
        }

        if (computes.size() != numCol)
        {
            error = true;
            int difference = numCol - computes.size();
            computes.clear();
            cout << difference << " computability " << (difference > 1 ? "are" : "is") << " missing" << endl;
            pressEnter();
        }
        return computes;
    }

    // Read number of row from data file
    int readRow(ifstream &file)
    {
        int row;
        file >> row;
        if (!row)
        {
            error = true;
            cout << "Number of row is missing" << endl;
            pressEnter();
            return 0;
        }
        file.ignore(100, '\n');
        return row;
    }

    // Combine readcol, readTitle, readCompute & readRow
    void readInfo(ifstream &file)
    {
        string line;

        numCol = readCol(file);
        if (error)
            return;

        title = readTitle(file);
        if (error)
            return;

        compute = readCompute(file);
        if (error)
            return;

        numRow = readRow(file);
        if (error)
            return;
    }

    // Check and convert string to integer
    int getInt(const string &strNum)
    {
        int intNum;
        stringstream stream;
        for (int i = 0; i < strNum.size(); i++)
        {
            if (!(isdigit(strNum[i])))
            {
                return -1;
            }
        }
        stream << strNum;
        stream >> intNum;
        if (intNum < 0)
        {
            return -1;
        }
        return intNum;
    }

    // Read and check the line of the data from the data file
    vector<int> getLineData(const string &line, const int &currentRow)
    {
        vector<int> row;
        stringstream ss;
        string strCol;
        int intCol;
        ss << line;
        while (getline(ss, strCol, ','))
        {
            intCol = getInt(strCol);
            if (intCol != -1)
            {
                row.push_back(intCol);
            }
        }
        if (row.size() == numCol)
        {
            return row;
        }
        else
        {
            error = true;
            int difference = numCol - row.size();
            cout << difference << " data in row " << currentRow + 1 << (difference > 1 ? " are" : " is") << " missing or invalid" << endl;
            row.clear();
            pressEnter();
            return row;
        }
    }

    // Read the data from the data file
    void readData(vector2d &data, int row)
    {
        string line;
        int countRow = 0;
        while (countRow < row)
        {
            getline(inFile, line);
            vector<int> d = getLineData(line, countRow);
            if (error)
            {
                pressEnter();
                return;
            }
            data.push_back(d);
            countRow++;
        }
        inFile.close();
        if (data.size() != numRow)
        {
            error = true;
            int difference = numRow - data.size();
            cout << difference << " row " << (difference > 1 ? "are" : "is") << " missing" << endl;
            pressEnter();
        }
    }

    // Combine the readInfo & readData
    void readFile(string path)
    {
        inFile.open(path);
        if (inFile)
        {
            readInfo(inFile);
            if (error)
            {
                inFile.close();
                return;
            }
            readData(data, numRow);
            if (error)
            {
                inFile.close();
                return;
            }
        }
        else
        {
            error = true;
            cout << "The file cannot open" << endl;
            pressEnter();
            return;
        }
    }

    // ------------------------------------------------------------------------

    // Check if the file exist or not
    bool fileExist(const string &path)
    {
        ifstream file(path);
        bool exist = file ? true : false;
        file.close();
        return exist;
    }

    // ------------------------------------------------------------------------

    // Check if the file name accepted by system
    bool properName(const string &filename)
    {
        char character[] = {'\\', '/', ':', '*', '?', '<', '>', '|'};
        for (int i = 0; i < filename.size(); i++)
        {
            for (char c : character)
            {
                if (c == filename[i])
                {
                    cout << "The filename cannot contain '\\', '/', ':', '*', '?', '<', '>', '|' character." << endl;
                    pressEnter();
                    return false;
                }
            }
        }
        return true;
    }

    // A screen will show if the file exists
    bool fileExistScreen()
    {
        string res;
        do
        {
            showHeader();
            cout << "The filename already exist" << endl;
            cout << "Type 'y' to replace and 'n' to set a new name" << endl;
            getline(cin, res);
            if (res != "y" && res != "n")
            {
                cout << "Please enter a valid input" << endl;
                pressEnter();
            }

        } while (res != "y" && res != "n");

        return res == "y" ? true : false;
    }

    // Ask the filename from the user
    void askFilename(string &filename)
    {
        while (true)
        {
            showHeader();
            cout << "What is the name of new file (without the file extension -> .txt)" << endl;
            cin >> filename;
            cin.ignore(50, '\n');
            if (!properName(filename))
                continue;

            filename += ".txt";
            string path = dataDir + slash + filename;
            if (fileExist(path))
            {
                if (!fileExistScreen())
                {
                    continue;
                }
            }
            break;
        }
    }

    // Write one integer data such as number of column/row into the file
    void writeLine(ofstream &file, const int &data)
    {
        file << data << endl;
    }

    // Write title into the file
    void writeLine(ofstream &file, const vecpair &data)
    {
        for (int i = 0; i < numCol; i++)
        {
            if (i != numCol - 1)
            {
                file << data[i].first << ",";
            }
            else
            {
                file << data[i].first;
            }
        }
        file << endl;
    }

    // Write a vector of data such as computable into the file
    void writeLine(ofstream &file, const vector<int> &data)
    {
        for (int i = 0; i < numCol; i++)
        {
            if (i != numCol - 1)
            {
                file << data[i] << ",";
            }
            else
            {
                file << data[i];
            }
        }
        file << endl;
    }

    // Write the data into the file
    void writeLine(ofstream &file, const vector2d &data)
    {
        for (int i = 0; i < numRow; i++)
        {
            for (int j = 0; j < numCol; j++)
            {
                if (j != numCol - 1)
                {
                    file << data[i][j] << ",";
                }
                else
                {
                    file << data[i][j];
                }
            }
            if (i < numRow - 1)
            {
                file << endl;
            }
        }
    }

    // ------------------------------------------------------------------------

    // Ask text report name from the user
    void askTxtName(string &filename)
    {
        while (true)
        {
            showHeader();
            cout << "What is the name of txt report (without file extension -> .txt)" << endl;
            cin >> filename;
            cin.ignore(50, '\n');
            if (!properName(filename))
                continue;
            filename += ".txt";
            string path = reportDir + slash + filename;
            if (fileExist(path))
            {
                if (!fileExistScreen())
                {
                    continue;
                }
            }
            break;
        }
    }

    // ------------------------------------------------------------------------

    // Ask html report name from the user
    void askHtmlName(string &filename)
    {
        while (true)
        {
            showHeader();
            cout << "What is the name of html report (without file extension -> .html)" << endl;
            cin >> filename;
            cin.ignore(50, '\n');
            if (!properName(filename))
            {
                cout << "The filename cannot contain '\\', '/', ':', '*', '?', '<', '>', '|' character.";
                continue;
            }
            filename += ".html";
            string path = htmlDir + slash + filename;
            if (fileExist(path))
            {
                if (!fileExistScreen())
                {
                    continue;
                }
            }
            break;
        }
    }
    // ------------------------------------------------------------------------

    // Show the content of text report
    void printTxtReport(string path)
    {
        ifstream file(path);
        string line;
        while (!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }
        file.close();
    }

    // ----------------------------------------------------------------------------------------------------------------------------------------------------
public:
    // typedef vector<vector<int>> vector2d;
    // typedef vector<pair<string, int>> vecpair;
    File(string username)
    {
        dir += slash + username;
        dataDir = dir + slash + "data";
        reportDir = dir + slash + "report";
        htmlDir = dir + slash + "html";
        system((mkdir + dataDir).c_str());
        system((mkdir + reportDir).c_str());
        system((mkdir + htmlDir).c_str());
        clearScreen();
    }

    // Screen that ask filename
    void loadScreen()
    {
        do
        {
            data.clear();
            title.clear();
            compute.clear();
            error = false;
            string path, fileName;

            showHeader();
            cout << "What is the filename (without file extension -> .txt)" << endl;
            getline(cin, fileName);
            path = dataDir + slash + fileName + ".txt";
            // cout << path << endl;
            readFile(path);
            if (error)
                continue;
            break;
        } while (error);
    }

    // Return number of column
    int getCol()
    {
        return numCol;
    }

    // Return titles
    vecpair getTitle()
    {
        return title;
    }

    // Return compute
    vector<int> getCompute()
    {
        return compute;
    }

    // Return number of row
    int getRow()
    {
        return numRow;
    }

    // Return data
    vector2d getData()
    {
        return data;
    }

    // Save the data file as another name
    void savedAs()
    {
        string filename, path;
        ofstream outFile;

        askFilename(filename);

        path = dataDir + slash + filename;
        outFile.open(path);
        writeLine(outFile, numCol);
        writeLine(outFile, title);
        writeLine(outFile, compute);
        writeLine(outFile, numRow);
        writeLine(outFile, data);

        cout << "Your data file is saved as '" << filename << "' successfully" << endl;
        pressEnter();
    }

    // Save the generated plain text report
    void saveTxtReport(const string &data)
    {
        ofstream outFile;
        string filename;
        string input;
        askTxtName(filename);
        string path = reportDir + slash + filename;
        outFile.open(path);
        outFile << data;
        outFile.close();
        while (true)
        {
            cout << "Do you want to view the report? Type 'y' to view or 'n' to skip" << endl;
            cin >> input;
            cin.ignore(50, '\n');
            if (input == "y")
            {
                cout << data << endl;
                pressEnter();
                return;
            }
            else if (input == "n")
            {
                return;
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
    }

    // Save the generated html report
    void saveHtmlReport(const string &data)
    {
        ofstream outFile;
        string filename;
        string input;
        askHtmlName(filename);
        string path = htmlDir + slash + filename;
        outFile.open(path);
        outFile << data;
        outFile.close();
        while (true)
        {
            cout << "Do you want to view the report? Type 'y' to view or 'n' to skip" << endl;
            cin >> input;
            cin.ignore(50, '\n');
            if (input == "y")
            {
                system(path.c_str());
                pressEnter();
                return;
            }
            else if (input == "n")
            {
                return;
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
    }

    // Screen that show plain text report
    void txtReportScreen()
    {
        string filename;
        while (true)
        {
            showHeader();
            cout << "Please enter the name of txt report (without file extension -> .txt)" << endl;
            cout << "Press enter to go back" << endl;

            getline(cin, filename);

            if (filename == "")
            {
                return;
            }
            filename += ".txt";
            string path = reportDir + slash + filename;
            if (fileExist(path))
            {
                printTxtReport(path);
                pressEnter();
                break;
            }
            else
            {
                cout << "The file cannot found" << endl;
                pressEnter();
            }
        }
    }

    // Screen that show html report
    void htmlReportScreen()
    {
        string filename;
        while (true)
        {
            showHeader();
            cout << "Please enter the name of html report (without file extension -> .html) " << endl;
            cout << "Press enter to go back" << endl;
            getline(cin, filename);
            if (filename == "")
            {
                return;
            }
            filename += ".html";
            string path = htmlDir + slash + filename;
            if (fileExist(path))
            {
                system(path.c_str());
                break;
            }
            else
            {
                cout << "The file cannot found" << endl;
                pressEnter();
            }
        }
    }
};

class Log
{
    string date, time, operation;
};

class Logger
{
private:
    string logPath, logDir = "Users_Folder";
    vector<string> logs;

    // Get current date and time
    string getCurrentTime()
    {
        stringstream t;
        string day, month, date, times, year;
        time_t now = time(0);
        t << ctime(&now);
        t >> day >> month >> date >> times >> year;
        return year + "-" + month + "-" + date + "  " + times;
    }

    // read log from the log file
    vector<string> readFile()
    {
        ifstream file(logPath);
        string log;
        stringstream ss;

        vector<string> logs;

        while (!file.eof())
        {
            getline(file, log);
            if (log != "")
            {
                logs.push_back(log);
            }
        }
        file.close();
        return logs;
    }

    // Show all log
    void showLogMenu(string options[], int &num, int &start, int &end)
    {
        vector<string> logs = readFile();
        for (int i = start; i < end && i < logs.size(); i++)
        {
            cout << logs[i] << endl;
        }

        cout << endl
             << endl;

        if (start != 0)
        {
            cout << num << ". Previous" << endl;
            options[num - 1] = "p";
            num++;
        }
        if (start + 10 < logs.size())
        {
            cout << num << ". Next" << endl;
            options[num - 1] = "n";
            num++;
        }
        cout << num << ". Go back" << endl;
        options[num - 1] = "g";
    }

    // Get and check input from the user
    bool getValidInput(int &i, int &num)
    {
        string input;
        cout << "Please enter your input" << endl;
        cin >> input;
        cin.ignore(30, '\n');
        if (isdigit(input[0]))
        {
            i = stoi(input);
        }
        else
        {
            cout << "Please enter a valid input" << endl;
            pressEnter();
            return false;
        }

        if (i < 1 || i > num)
        {
            cout << "Please enter a valid input" << endl;
            pressEnter();
            return false;
        }

        return true;
    }

public:
    Logger(string username)
    {
        logDir += slash + username + slash + "log";
        string createDir = mkdir + logDir;
        system(createDir.c_str());
        clearScreen();
        logPath += logDir + slash + "log.txt";
    }

    // Log and write into the log file
    void log(string operation)
    {
        ofstream file(logPath, ios::app);
        file << left;
        file << setw(25) << getCurrentTime() << operation << endl;
        file.close();
    }

    // Screen that show all log
    void showLogScreen()
    {
        int start = 0, end = 10, input;
        while (true)
        {
            string options[3];
            int num = 1;

            showHeader();
            showLogMenu(options, num, start, end);
            if (!getValidInput(input, num))
                continue;

            if (options[input - 1] == "p")
            {
                start = start - 10;
                end = end - 10;
            }
            else if (options[input - 1] == "n")
            {
                start = start + 10;
                end = end + 10;
            }
            else if (options[input - 1] == "g")
                break;
        }
    };
};
