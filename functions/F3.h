#include <iostream>
#include <algorithm> // for sort
#include <cmath> // for pow

using namespace std;

// find a specific column or all columns
int select_column()
{
    cout << "Specific column or all column?"
            << " (1 for specific, 2 for all): ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter the column number: ";
        int column;
        cin >> column;
        return column;
    }
    else if (choice == 2)
    {
        return -1;
    }
    else
    {
        cout << "Invalid input.\n";
        return select_column();
    }
}


//find min from a 2d array
int find_min(int arr[][3] , int row, int column)
{
    int min = arr[0][column];
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
int find_max(int arr[][3] , int row, int column)
{
    int max = arr[0][column];
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
double find_median(int arr[][3] , int row, int column)
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

double find_mean(int arr[][3] , int row, int column)
{
    double sum = 0;
    for (int i = 0; i < row; i++)
    {
        sum += arr[i][column];
    }
    return sum / row;
}

double find_variance(int arr[][3] , int row, int column)
{
    double mean = find_mean(arr, row, column);
    double sum = 0;
    for (int i = 0; i < row; i++)
    {
        sum += pow(arr[i][column] - mean, 2);
    }
    return sum / row;
}

double find_stdv(int arr[][3] , int row, int column)
{
    double variance = find_variance(arr, row, column);
    return sqrt(variance);
}



// Allocates dynamic array
int **allocateArray(int row, int col)
{
    int **arr;
    arr = new int*[row];
    for (int i=0; i<row; i++)   
        arr[i] = new int[col];
    return arr;
}

//Free dynamic array
void freeArray(int **arr, int row)
{
    for (int i=0; i<row; i++)   
        delete[] arr[i];
    delete[] arr;
}