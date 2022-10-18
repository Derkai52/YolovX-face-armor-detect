#ifndef YOLOXARMOR_GENERAL_H
#define YOLOXARMOR_GENERAL_H

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>


using namespace std;
using namespace cv;

/**
 * @brief 存储任务所需数据的结构体
 *
 */
struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};

float calcTriangleArea(cv::Point2f pts[3]);
float calcTetragonArea(cv::Point2f pts[4]);
double rangedAngleRad(double &angle);

#endif //YOLOXARMOR_GENERAL_H
