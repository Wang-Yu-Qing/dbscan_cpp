#include <set>
#include <iostream>
#include "common.h"
#include "dbscan.h"
#include "sample_point.h"
#include <cmath>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

DBSCAN::DBSCAN(list<Sample_point> &input_data, double radius, int minimum_points)
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
    // 防止一个点被重复计算邻居
    if (p.visited)
        throw invalid_argument("Point has already been visited!");
    // 使用地址查看是否另一个点就是自己
    for (Sample_point &another_p : this->input_data) // 这里一定要通过引用迭代，否则后面添加的是复制变量的地址，该地址循环中全部都一样！
    {
        if (&another_p != &p)
        {
            double distance = this->compute_distance(p, another_p);
            if (distance == 0) {
                another_p.show_vector();
                p.show_vector();
            }
            if (distance <= this->radius)
            {
                // cout << distance << endl;
                // 使用样本点的指针，来追踪样本点
                // cout << &another_p << endl;
                p.neighbours.push_back(&another_p);
            }
        }
    }
    p.visited = true;
    // cout << "number of neighbours: " << p.neighbours.size();
}


void DBSCAN::spread_cluster(Sample_point &spreader, int cluster)
{
    cout << "start spreading" << endl;
    for (Sample_point *neighbour : spreader.neighbours)
    {
        if (!(*neighbour).visited)
        {
            // 将该点的邻居，添加至spreader的邻居里
            this->find_neighbours(*neighbour);
            for (Sample_point *remote_neighbour : neighbour->neighbours)
            {
                spreader.neighbours.push_back(remote_neighbour); // 使用vector的话，可能造成连续的存储空间转移，当前的迭代变量失效
            }
        }
        if (neighbour->cluster == -1)
            neighbour->cluster = cluster;
    }
    cout << "spread done" << endl;
}

vector<int> DBSCAN::run()
{
    // dbscan主算法
    int current_cluster = 0;
    for (Sample_point &point : this->input_data)
    {
        if (!point.visited)
        {
            // 更新该点的所有邻居
            this->find_neighbours(point);
            // 若该点不是噪声点，则传播新的类别
            if (point.neighbours.size() >= this->minimum_points)
            {
                cout << "found core point for new cluster" << endl;
                current_cluster += 1;
                point.cluster = current_cluster;
                this->spread_cluster(point, current_cluster);
            }
        }
    }
    // 获取结果
    vector<int> result;
    for (Sample_point point : this->input_data)
    {
        result.push_back(point.cluster);
    }
    return result;
}

int main()
{
    // 读取csv文件
    csv_read_result data = read_csv("data/gaode_merge.csv");
    // 初始化每行的点对象
    list<Sample_point> samples;
    for (row row_values : data)
    {
        try
        {
            // 使用经纬度作为特征值
            vector<double> vec = {stod(row_values[3]), stod(row_values[4])};
            Sample_point sample(vec);
            samples.push_back(sample); // 在循环体内部创建的变量，出了循环体后会被销毁，若存指针或引用，会因原变量被销毁而造成内存错误，因此存拷贝。
        }
        catch (invalid_argument)
        {
            cout << "skip the row with chars that cannot convert to double." << endl;
            cout << row_values[3] << ", " << row_values[4] << endl;
        }
    }
    // 构造DBSCAN对象
    DBSCAN model(samples, 0.01, 100);
    vector<int> clusters = model.run();
    cout << "cluster done." << endl;
    int number_of_clusters = set<double>(clusters.begin(), clusters.end()).size();
    cout << "found " << number_of_clusters << " clusters" << endl;
    // 保存结果至csv文件中
    vector<string> rows;
    for (Sample_point point : model.input_data)
    {
        string row_string = "";
        for (double &value : point.vec)
        {
            row_string += (to_string(value) + ",");
        }
        row_string += (to_string(point.cluster) + "\n");
        rows.push_back(row_string);
    }
    write_csv("data/result.csv", rows);
    return 1;
}