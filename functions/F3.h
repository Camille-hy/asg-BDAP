#include <iostream>
#include <algorithm> // for sort
#include <cmath> // for pow
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

// find a specific column or all columns
char select_column()
{
    cout << "Specific column or all column?"
            << " (1 for specific, 2 for all): ";
    char choice;
    cin >> choice;
    return choice;
}


//find min from a 2d array
double find_min(vector2d arr , int row, int column)
{
    double min = arr[0][column];
    for (int i = 0; i < row; i++)
    {
        if (arr[i][column] < min)
        {
            min = arr[i][column];
        }
    }
    return min;
}


// find max from a 2d array
double find_max(vector2d arr , int row, int column)
{
    double max = arr[0][column];
    for (int i = 0; i < row; i++)
    {
        if (arr[i][column] > max)
        {
            max = arr[i][column];
        }
    }
    return max;
}

// find median from a 2d array
double find_median(vector2d arr , int row, int column)
{
    double median = 0;
    double temp[row];
    for (int i = 0; i < row; i++)
    {
        temp[i] = arr[i][column];
    }
    sort(temp, temp + row);
    if (row % 2 == 0)
    {
        median = (temp[row / 2] + temp[row / 2 - 1]) / 2;
    }
    else
    {
        median = temp[row / 2];
    }
    return median;
}

double find_mean(vector2d arr , int row, int column)
{
    double sum = 0;
    for (int i = 0; i < row; i++)
    {
        sum += arr[i][column];
    }
    return sum / row;
}

double find_variance(vector2d arr, int row, int column)
{
    double mean = find_mean(arr, row, column);
    double sum = 0;
    for (int i = 0; i < row; i++)
    {
        sum += pow(arr[i][column] - mean, 2);
    }
    return sum / row;
}

double find_stdv(vector2d arr , int row, int column)
{
    double variance = find_variance(arr, row, column);
    return sqrt(variance);
}



// // Allocates dynamic array
// int **allocateArray(int row, int col)
// {
//     int **arr;
//     arr = new int*[row];
//     for (int i=0; i<row; i++)   
//         arr[i] = new int[col];
//     return arr;
// }

// //Free dynamic array
// void freeArray(int **arr, int row)
// {
//     for (int i=0; i<row; i++)   
//         delete[] arr[i];
//     delete[] arr;
// }


// -----------------------------------------------------------------------------------
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


// -----------------------------------------------------------------------------------


vector<vector<int>> classInterval(int min, int max, int row) {
  int c;
  vector<vector<int>> interval;
  c = ceil(1 + (3.3 * log10(row)));
  int classWidth = ceil((max - min) / float(c));
  int lowerBoundary = min;
  int upperBoundary = min + classWidth - 1;

  for (int i = 0; i < c; i++) {
    vector<int> temp = {lowerBoundary, upperBoundary};
    interval.push_back(temp);
    // 125
    lowerBoundary += classWidth;
    // 129
    upperBoundary += classWidth;
  }
  return interval;
}

vector<pair<double, int>> countData(vector2d data,
                                    vector<vector<int>> interval, int index) {
  vector<pair<double, int>> count;
  for (auto i : interval) {
    int counter = 0;
    for (auto d : data) {
      if (d[index] >= i[0] && d[index] <= i[1]) {
        counter++;
      }
    }
    double midpoint = (i[0] + i[1]) / 2.0;
    pair<double, int> temp = {midpoint, counter};
    count.push_back(temp);
  }
  return count;
}

string createTable(vector<pair<double, int>> count) {
  stringstream table;

  table << setprecision(1) << fixed;
  table << left;
  table << "Counts\t"
        << "Mid-points" << endl;
  for (int i = count.size() - 1; i >= 0; i--) {
    table << setw(10) << count[i].second << setw(4) << count[i].first << "|";
    for (int j = 0; j < count[i].second; j++) {
      table << "=";
    }
    table << endl;
  }
  table << setw(14) << ""
        << "+---------+---------+---------+---------+---------+" << endl;
  table << setw(14) << ""
        << "0         10        20        30        40        50" << endl;
  return table.str();
}

string histogram(vector2d data, int min, int max, int row, int index) {
  vector<vector<int>> interval = classInterval(min, max, row);
  vector<pair<double, int>> count = countData(data, interval, index);
  string table = createTable(count);
  cout << table;
  return table;
}

double correlation(vector<vector<int>> data,int row,int x,int y)
{
    double correlation, sumXY=0, sumX2=0, sumY2=0;
    double mean_x = find_mean(data, row, x);
    double mean_y = find_mean(data, row, y);
    for(int i=0;i<row;i++)
    {
        sumXY += data[i][x] * data[i][y];
        sumX2 += pow((data[i][x]), 2);
        sumY2 += pow((data[i][y]), 2);
    }
    double numerator = sumXY - (row*mean_x*mean_y);
    double mean_x2 = pow(mean_x, 2);
    double mean_y2 = pow(mean_y, 2);
    double denominator = (sqrt(sumX2 - row*mean_x2)) * (sqrt(sumY2 - row*mean_y2));
    correlation = numerator / denominator;

    return correlation;
}


// Show Computable Titles
void showComputableTitles(vecpair titles, vector<int> computable)
{
  
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
}

double returnFunction(char choice, vector2d arr2d, int row, int index)
{
  if (choice == '1')
    return find_min(arr2d, row, index);
  else if (choice == '2')
    return find_max(arr2d, row, index);
  else if (choice == '3')
    return find_median(arr2d, row, index);
  else if (choice == '4')
    return find_mean(arr2d, row, index);
  else if (choice == '5')
    return find_variance(arr2d, row, index);
  else if (choice == '6')
    return find_stdv(arr2d, row, index);
  return 0;
}

double singleColumnCompute
(string method,
char &choice,
vecpair titles, 
vector<int> computable,
vector2d arr2d, 
int row,
bool &flag2)
{
  int choiceindex;
  cout << "Select title by index" << endl;
  cin >> choiceindex;
  int index = choiceindex - 1;

  // if choiceto int is in between 0 to computable.size()
  if ((choiceindex >= 0) && (choiceindex <= computable.size()))
  {
    if (computable[index] == 1)
    {
      double result = returnFunction(choice, arr2d, row, index);
      cout << method << " of " 
          << titles[index].first << ": " 
          << result << endl;

      flag2 = true;
      return result;
    }
    else
    {
      cout << "Error: Title not computable" << endl;
    }
  }
  else
  {
    cout << "Error: Invalid index" << endl;
  }
  return 0;
}

string allColumnCompute(string method, vecpair titles, vector<int> computable, char choice, vector2d arr2d, int row)
{
  stringstream ss;
  for (int i = 0; i < titles.size(); i++)
    {
      if (computable[i] == 1)
      {
          double result = returnFunction(choice, arr2d, row, i);
          ss << method << " of " 
              << titles[i].first << ": " 
              << result << endl;

      }
    }
    cout << ss.str();
    return ss.str();
}