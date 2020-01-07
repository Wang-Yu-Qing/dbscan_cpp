#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include "declarations.h"

using namespace std;



csv_result read_csv(string);

csv_result read_csv(string file_path)
{
    ifstream file_stream(file_path);
    string line;
    vector<vector<string>> values;
    while (getline(file_stream, line))
    {
        string line_value;
        row line_values;
        stringstream line_stream(line);
        while (getline(line_stream, line_value, ','))
        {
            line_values.push_back(line_value);
        }
        values.push_back(line_values);
    }
    return values;
}

int main()
{
    csv_result result = read_csv("data/gaode_merge.csv");
    for (row row_values : result)
    {
        for (string value : row_values)
        {
            cout << value << ",";
        }
        cout << endl << "====" << endl;
    }
    return 0;
}