#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<pair<int, int>> distinctMember(vector<vector<int>> data, int col)
{
    vector<int> distincts;
    vector<pair<int, int>> distinctCount;
    pair<int, int> temp;

    for (auto row : data)
    {
        if (find(distincts.begin(), distincts.end(), row[col]) == distincts.end())
            distincts.push_back(row[col]);
    }

    sort(distincts.begin(), distincts.end());

    for (auto num : distincts)
    {
        int count = 0;
        for (auto row : data)
        {
            if (num == row[col])
                count++;
        }
        temp.first = num;
        temp.second = count;
        distinctCount.push_back(temp);
    }
    return distinctCount;
}

string tabularForm(vector<pair<int, int>> data)
{
    string form;
    stringstream ss;
    string temp;
    // form += "Distinct Number | Count\n";
    ss << "+-----------------+-------+" << endl;
    ss << "| Distinct Number | Count |" << endl;
    ss << "+-----------------+-------+" << endl;
    for (auto p : data)
    {
        ss << "|" << setw(9) << p.first << setw(9)
           << "|" << setw(4) << p.second << setw(4)
           << "|" << endl;
    }
    ss << "+-----------------+-------+" << endl;
    form = ss.str();
    cout << form;

    return form;
}