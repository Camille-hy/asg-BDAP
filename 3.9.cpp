#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> data = {51, 70, 79, 75, 72, 55, 25, 38, 74, 54, 37, 15, 56, 17, 77,
                    43, 16, 15, 72, 92, 25, 30, 24, 46, 47, 46, 45, 38, 81, 49};

vector<vector<int>> classInterval(vector<int> data) {
  int c, min = 15, max = 92;
  vector<vector<int>> interval;

  c = ceil(1 + (3.3 * log10(data.size())));
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

vector<pair<double, int>> countData(vector<int> data,
                                    vector<vector<int>> interval) {
  vector<pair<double, int>> count;
  for (auto i : interval) {
    int counter = 0;
    for (auto d : data) {
      if (d >= i[0] && d <= i[1]) {
        counter++;
      }
    }
    double midpoint = (i[0] + i[1]) / 2;
    pair<int, double> temp = {midpoint, counter};
    count.push_back(temp);
  }
  return count;
}

string createTable(vector<pair<double, int>> count) {
  stringstream table;

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

int main() {
  vector<vector<int>> interval = classInterval(data);
  vector<pair<double, int>> count = countData(data, interval);
  string table = createTable(count);
  cout << table;
  return 0;
}
