#include <iostream>
#include <vector>
#include <string>
#include "common.h"
#include "sample_point.h"

using namespace std;

// 构造函数定义
Sample_point::Sample_point(vector<double> vector)
{
    this->vec = vector;
    this->visited = false;
    this->cluster = -1;
}

Sample_point::~Sample_point(){}

void Sample_point::show_vector() {
    cout << "{";
    for (double value:this->vec){
        cout << value << ",";
    }
    cout << "}" << endl;
}

int Sample_point::dimensions() {
    return (this->vec).size();
}
