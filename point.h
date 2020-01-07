#pragma once

#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
using namespace std;

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
#endif
