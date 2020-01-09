#ifndef DECLAR_H_
#define DECLAR_H_

#include <string>
#include <vector>
using namespace std;

enum is_visited{not_visited, visited};
typedef vector<string> row;
typedef vector<row> csv_read_result;

csv_read_result read_csv(string);
string join_strings_in_vector(row&, string&);
void write_csv(string, vector<string>);



#endif
