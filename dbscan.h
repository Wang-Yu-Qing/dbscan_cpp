#ifndef DBSCAN_H_
#define DBSCAN_H_

#include "common.h"
#include "sample_point.h"

class DBSCAN
{
public:
    vector<Sample_point> input_data;
    int number_of_clusters;
    double radius;
    int minimum_points;
    DBSCAN(vector<Sample_point> input_data, double radius, int minimum_points);
    ~DBSCAN();
    double compute_distance(Sample_point, Sample_point);
    void find_neighbours(Sample_point&);
    vector<int> run();

};

#endif