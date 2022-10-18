#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "inference.h"

using namespace std;
using namespace cv;

cv::Mat ori_src;
cv::Mat image2show;
VideoCapture capture;
ArmorDetector detector;

void display(ArmorObject);

int main() {
    // 选择视频源 (1、免驱相机  0、视频文件)
    int from_camera = 0;

    if (from_camera) {
        capture.open(0);
    } else {
        string filename = PROJECT_DIR"/videoTest/armor_red.avi";
        capture.open(filename);
    }
    if(!capture.isOpened()){
        printf("video can not open ...\n");
        return -1;
    }

    // 初始化网络模型
    const string network_path = PROJECT_DIR"/model/opt-0517-001.xml";
    detector.initModel(network_path);

    while (true){
        auto time_start=std::chrono::steady_clock::now();
        if (from_camera) {
            capture.read(ori_src); // 相机取图
            if (ori_src.empty()) { // 相机开启线程需要一定时间
                continue;
            }
        } else {
            capture.read(ori_src);
        }

        vector<ArmorObject> objects;  // 创建装甲板目标属性容器
        image2show = ori_src; // 可视化图像
        Mat input = ori_src;  // 网络推理图像
        if (detector.detect(input, objects)){ // 前向推理获得目标结果
            for (auto armor_object : objects){
                display(armor_object); // 识别结果可视化
            }
        }

        auto time_predict = std::chrono::steady_clock::now();
        double dr_full_ms = std::chrono::duration<double,std::milli>(time_predict - time_start).count();
        putText(image2show, "FPS: "+to_string(int(1000 / dr_full_ms)), {10, 25}, FONT_HERSHEY_SIMPLEX, 1, {0,255,0});
        cout <<"[AUTOAIM] LATENCY: "<< " Total: " << dr_full_ms << " ms"<< endl;

        imshow("output", image2show);
        waitKey(1);
    }
    return 0;
}

void display(ArmorObject object) {
    // 绘制十字瞄准线
    line(image2show, Point2f(image2show.size().width / 2, 0), Point2f(image2show.size().width / 2, image2show.size().height), {0,255,0}, 1);
    line(image2show, Point2f(0, image2show.size().height / 2), Point2f(image2show.size().width, image2show.size().height / 2), {0,255,0}, 1);

    // 绘制四点
    for (int i = 0; i < 4; i++) {
        circle(image2show, Point(object.apex[i].x, object.apex[i].y), 3, Scalar(100, 200, 0), 5);
    }
    // 绘制左上角顶点
    circle(image2show, Point(object.apex->x, object.apex->y),3,Scalar(255, 255, 0),8 );

    // 绘制装甲板四点矩形
    for (int i = 0; i < 4; i++) {
        line(image2show, object.pts[i], object.pts[(i + 1) % 4], Scalar(100, 200, 0), 3);
    }

    // 绘制目标颜色与类别
    int id = object.cls;
    int box_top_x = object.apex->x;
    int box_top_y = object.apex->y;
    if (object.color == 0)
        cv::putText(image2show, "Blue_"+to_string(id), Point(box_top_x + 2, box_top_y), cv::FONT_HERSHEY_TRIPLEX, 1,
                    Scalar(255, 0, 0));
    else if (object.color == 1)
        cv::putText(image2show, "Red_"+to_string(id), Point(box_top_x + 2, box_top_y), cv::FONT_HERSHEY_TRIPLEX, 1,
                    Scalar(0, 0, 255));
    else if (object.color == 2)
        cv::putText(image2show, "None_"+to_string(id), Point(box_top_x + 2, box_top_y), cv::FONT_HERSHEY_TRIPLEX, 1,
                    Scalar(0, 255, 0));
}