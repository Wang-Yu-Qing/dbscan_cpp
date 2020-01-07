#pragma once

#ifndef DECLAR_H_
#define DECLAR_H_

#include <string>
#include <vector>
using namespace std;


typedef vector<string> row;
typedef vector<row> csv_result;


class Point
{
private:
    vector<Point> neighbours;

public:
    vector<double> vec;
    string type;
    bool visited;
    int cluster;
    Point(vector<double> vec);
    ~Point();
    void show_vector();
};

class DBSCAN
{
public:
    csv_result input_data;
    int number_of_clusters;
    DBSCAN(csv_result input_data);
    ~DBSCAN();
    double compute_distance(Point, Point);
    vector<int> run();
};
#endif
