#ifndef DBSCAN_H_
#define DBSCAN_H_

#include "common.h"
#include "sample_point.h"

class DBSCAN
{
public:
    list<Sample_point> input_data;
    int number_of_clusters;
    double radius;
    int minimum_points;
    DBSCAN(list<Sample_point> &input_data, double radius, int minimum_points);
    ~DBSCAN();
    inline double compute_distance(Sample_point&, Sample_point&);
    void find_neighbours(Sample_point&);
    void spread_cluster(Sample_point&, int);
    void result_to_csv(string);
    vector<int> run();
};

#endif