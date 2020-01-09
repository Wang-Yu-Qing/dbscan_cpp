#ifndef SAMPLE_POINT_H_
#define SAMPLE_POINT_H_

#include <string>
#include <vector>

using namespace std;

class Sample_point
{

public:
    vector<double> vec;
    vector<Sample_point*> neighbours;
    string type;
    // bool visited;
    is_visited visited;
    int cluster;
    Sample_point(vector<double>);
    ~Sample_point();
    int dimensions();
    void show_vector();
};


#endif

