#include <iostream>
#include <vector>
#include <string>
#include "point.h"

using namespace std;

// 构造函数定义
Point::Point(vector<double> vector)
{
    this->vec = vector;
    this->visited = false;
    this->cluster = -1;
}

Point::~Point(){}

void Point::show_vector() {
    cout << "{";
    for (double value:this->vec){
        cout << value << ",";
    }
    cout << "}" << endl;
}

int main()
{
    Point p(vector<double>{1, 2});
    p.show_vector();
    return 1;
}