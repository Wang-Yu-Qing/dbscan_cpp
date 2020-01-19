#include <iostream>
#include <vector>
#include <string>
#include "common.h"
#include "sample_point.h"
#include <iomanip>

using namespace std;

// 构造函数定义
Sample_point::Sample_point(vector<double> vector)
{
    this->vec = vector;
    this->visited = false;
    // this->visited = not_visited;
    this->cluster = -1; // 先默认所有点都是噪声点
}

Sample_point::~Sample_point(){}

void Sample_point::show_vector() {
    cout << "{";
    for (double value:this->vec){
        cout << setprecision(17) << value << ",";
    }
    cout << "}" << endl;
}

int Sample_point::dimensions() {
    return (this->vec).size();
}
