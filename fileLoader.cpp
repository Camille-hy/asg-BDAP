#include <iostream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class File
{
private:
    typedef vector<vector<int>> vector2d;
    string user, file, dir = "user", dataDir, reportDir, htmlDir, logDir;
    vector<string> title;
    vector2d data;

    int getInt(string num)
    {
        for (int i = 0; i < num.size(); i++)
        {
            if (!(isdigit(num[i]) || num[i] == '.'))
            {
                return -1;
            }
        }
        return stoi(num);
    }

    vector<int> getData(string line, int currentRow)
    {
        vector<int> row;
        stringstream cols;
        cols << line;
        string strCol;
        int countCol = 0;
        int col;
        while (cols >> strCol)
        {
            col = getInt(strCol);
            if (col == -1)
            {
                row.clear();
                cout << "The data in row " << currentRow << " col " << countCol + 1 << " is invalid." << endl;
                return row;
            }
            row.push_back(col);
            countCol++;
        }

        if (countCol == numCol)
        {
            cout << "ok" << endl;
            return row;
        }
        else
        {
            cout << "missing" << endl;
            row.clear();
            cout << "Some data in row " << currentRow << " is missing" << endl;
            return row;
        }
    }

    vector<string> getTitle(string line)
    {
        vector<string> row;
        stringstream cols;
        cols << line;
        string col;
        int countCol = 0;
        while (cols >> col)
        {
            row.push_back(col);
            countCol++;
        }

        if (countCol = numCol)
        {
            return row;
        }
        else
        {
            row.clear();
            cout << "Some title is missing" << endl;
            return row;
        }
    }

    bool properName(string filename)
    {
        char character[] = {'\\', '/', ':', '*', '?', '<', '>', '|'};
        for (int i = 0; i < filename.size(); i++)
        {
            for (char c : character)
            {
                if (c == filename[i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    void writeLine(ofstream &file, int data)
    {
        file << data << endl;
    }

    void writeLine(ofstream &file, vector<string> data)
    {
        for (string str : data)
        {
            file << str << " ";
        }
        file << endl;
    }

    void writeLine(ofstream &file, vector2d data)
    {
        for (int i = 0; i < numRow; i++)
        {
            for (int col : data[i])
            {
                file << col << " ";
            }
            cout << i << endl;
            if (i < numRow - 1)
            {
                file << endl;
            }
        }
    }

    bool fileExist(string filename)
    {
        ifstream file(filename);
        return file ? true : false;
    }

public:
    int numCol, numRow;
    // vector<string> title;
    File(string username)
    {
        dir += "/" + username;
        dataDir = dir + "/data";
        reportDir = dir + "/report";
        htmlDir = dir + "/html";
        logDir = dir + "/log";
    }

    vector2d load()
    {
        bool fileError = true;

        while (fileError)
        {
            // vector2d data;
            data.clear();
            ifstream inFile;
            string line, path;
            int countRow = 1;
            cout << "What is the filename" << endl;
            getline(cin, file);
            path = dataDir + "/" + file;
            // cout << path << endl;
            inFile.open(path);

            if (inFile)
            {
                countRow = 1;
                inFile >> numCol;
                inFile.ignore(100, '\n');
                // cout << numCol << endl;
                getline(inFile, line);
                title = getTitle(line);
                inFile >> numRow;
                inFile.ignore(100, '\n');
                bool lineError = false;
                while (!inFile.eof())
                {
                    // cout << countRow<< endl;
                    getline(inFile, line);
                    vector<int> d = getData(line, countRow);
                    if (d.empty())
                    {
                        lineError = true;
                        break;
                    }
                    else
                    {
                        data.push_back(d);
                        countRow++;
                    }
                }
                if (lineError)
                {
                    inFile.close();
                    continue;
                }
                // cout << countRow << endl;
                if (countRow - 1 == numRow)
                {
                    // cout << "success";
                    fileError = false;
                    inFile.close();
                    return data;
                }
                else if (countRow == 1 & data.empty())
                {
                    cout << "The file is empty" << endl;
                    // return data;
                }
                else
                {
                    data.clear();
                    cout << "The number row of data is " << countRow - 1 << " which is not matched with" << numRow << "row state in file";
                    // return data;
                }
            }
            else
            {
                cout << "The file cannot open properly" << endl;
            }
        }
    }

    vector<string> getTitle()
    {
        return title;
    }

    void savedAs()
    {
        string filename, path;
        ofstream outFile;
        cout << "What is the name of new file" << endl;
        cin >> filename;
        while (true)
        {
            cout << "What is the name of new file" << endl;
            cin >> filename;
            cin.ignore(50,'\n');
            if (!properName(filename))
            {
                cout << "The filename cannot contain '\\', '/', ':', '*', '?', '<', '>', '|' character.";
                continue;
            }
            if (fileExist(filename))
            {
                cout << "The filename already exist" << endl;
                cout << "Type yes to replace and no to set a new name" << endl;
                string res;
                getline(cin, res);
                if (res == "no")
                {
                    continue;
                }
            }
            break;
        }
        path = dataDir + "/" + filename;
        outFile.open(path);
        writeLine(outFile, numCol);
        writeLine(outFile, title);
        writeLine(outFile, numRow);
        writeLine(outFile, data);
    }
};