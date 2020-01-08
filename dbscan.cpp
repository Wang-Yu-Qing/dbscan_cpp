#include <iostream>
#include "common.h"
#include "dbscan.h"
#include "sample_point.h"
#include <cmath>
#include <string>

using namespace std;

DBSCAN::DBSCAN(vector<Sample_point> input_data, double radius, int minimum_points)
{
    this->radius = radius;
    this->minimum_points = minimum_points;
    this->input_data = input_data;
}

DBSCAN::~DBSCAN() {}

// 频繁调用该函数，因此设为内联函数
inline double DBSCAN::compute_distance(Sample_point &p1, Sample_point &p2)
{
    double distance = 0;
    int dim = p1.dimensions();
    for (int i = 0; i < dim; i++)
    {
        distance += pow(p1.vec[i] - p2.vec[i], 2);
    }
    return sqrt(distance);
}

void DBSCAN::find_neighbours(Sample_point &p)
{
    int index = 0;
    // 使用引用查看是否另一个点就是自己
    for (Sample_point &another_p : this->input_data)
    {
        if (&another_p != &p)
        {
            // cout << distance << endl;
            if (this->compute_distance(p, another_p) <= this->radius)
            {
                p.neighbours.push_back(index);
            }
        }
        else
        {
            // cout << "found itself" << endl;
        }
        index += 1;
    }
}

vector<int> DBSCAN::run()
{
    cout << "Start find neighbours for each sample point.." << endl;
    // 这里也要使用引用传递
    for (Sample_point &p : this->input_data)
    {
        this->find_neighbours(p);
    }
    return vector<int>{1};
}

int main()
{
    // 读取csv文件
    csv_result data = read_csv("data/gaode_merge.csv");
    // 初始化每行的点对象
    vector<Sample_point> samples;
    for (row row_values : data)
    {
        try
        {
            vector<double> vec = {stod(row_values[3]), stod(row_values[4])};
            Sample_point sample(vec);
            samples.push_back(sample);
        }
        catch (invalid_argument)
        {
            cout << "skip the row with chars that cannot convert to double." << endl;
            cout << row_values[3] << ", " << row_values[4] << endl;
        }
    }
    // 构造DBSCAN对象
    DBSCAN model(samples, 0.05, 10);
    model.run();

    return 1;
}