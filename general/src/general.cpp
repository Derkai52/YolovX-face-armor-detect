#include "general.h"

/**
 * @brief 海伦公式计算三角形面积
 * 
 * @param pts 三角形顶点
 * @return float 面积
 */
float calcTriangleArea(cv::Point2f pts[3])
{
    auto a = sqrt(pow((pts[0] - pts[1]).x, 2) + pow((pts[0] - pts[1]).y, 2));
    auto b = sqrt(pow((pts[1] - pts[2]).x, 2) + pow((pts[1] - pts[2]).y, 2));
    auto c = sqrt(pow((pts[2] - pts[0]).x, 2) + pow((pts[2] - pts[0]).y, 2));
    auto p = (a + b + c) / 2.f;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

/**
 * @brief 计算四边形面积
 * 
 * @param pts 四边形顶点
 * @return float 面积
 */
float calcTetragonArea(cv::Point2f pts[4])
{
    return calcTriangleArea(&pts[0]) + calcTriangleArea(&pts[1]);
}

/**
 * @brief 将角度限制在[-PI,PI]的范围内
 * @return 处理后的角度
*/
double rangedAngleRad(double &angle)
{
    if (fabs(angle) >= CV_PI)
    {
        angle -= (angle / fabs(angle)) * CV_2PI;
        angle = rangedAngleRad(angle);
    }
    return angle;
}