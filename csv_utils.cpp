#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include "common.h"

using namespace std;

csv_read_result read_csv(string file_path)
{
    ifstream file_stream(file_path);
    string line;
    csv_read_result values;
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
    file_stream.close();
    return values;
}

string join_strings_in_vector(row &vec, string &delimma) {
    string result = "";
    for (string value : vec) {
        result += (value + delimma);
    }
    result.pop_back();
    return result;
}

void write_csv(string file_path, vector<string> rows) {
    string delimma = ",";
    ofstream file_stream(file_path);
    for (string row_to_write: rows) {
        // cout << row_to_write << endl;
        file_stream << row_to_write;
    }
    file_stream.close();
}
