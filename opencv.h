//
// Created by bp on 8/13/21.
//
#ifndef CAPSTONE_OPENCV_H
#define CAPSTONE_OPENCV_H
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <memory>
#include <QMetaType>


using namespace std;
using namespace cv;
using namespace dnn;

class OpenCV {
public:
    OpenCV();
    void CreateClassifier();
    void RunClassifier(std::string filename);
    void setTopConfidence(double x);
    double GetTopConfidence();
    int GetHotDogCount();

private:

    void DrawBoxes(int classId, float confidence, int left, int top, int right, int bottom, Mat &frame);
    void PostProcess(Mat &frame, const vector<Mat> &outputs);
    vector<string> classes;
    Net net;
    double confidence_{.5};
    double top_confidence_{0};
    int hot_dog_count_{0};
};

#endif //CAPSTONE_OPENCV_H
