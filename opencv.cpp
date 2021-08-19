#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv.h"

using namespace cv;
using namespace dnn;
using namespace std;

// Get the names of the output layers
vector<String> GetOutputLayerNames(const Net &net);

OpenCV::OpenCV() {
    CreateClassifier();
}

void OpenCV::CreateClassifier(){
        string classesFile = "../input/coco.names";
        ifstream ifs(classesFile.c_str());
        string line;
        while (getline(ifs, line))
            classes.emplace_back(line);

        // load classifier and store classifier in memory
        net = readNetFromDarknet("../input/yolov3.cfg", "../input/yolov3.weights");
}

void OpenCV::RunClassifier(std::string filename){
    Mat image = imread(filename);

    //resize image to make sure that confidence box looks same across all image resolutions
    resize(image, image, Size(416,416));
    Mat blob = blobFromImage(image, 1 / 255.0, cv::Size(416, 416), Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    // Runs the forward pass to get output of the output layers
    vector<Mat> outputLayers;
    // pass net by reference as const
    net.forward(outputLayers, GetOutputLayerNames(net));

    // Remove the bounding boxes with low confidence
    PostProcess(image, outputLayers);

    // Write the frame with the detection boxes
    imwrite("../output/processed_image.jpeg", image);
}



    // Remove the bounding boxes with low confidence
    void OpenCV::PostProcess(Mat &frame, const vector<Mat> &outputs){
        vector<int> class_id;
        vector<float> confidences;
        vector<Rect> boxes;

        for (size_t i = 0; i < outputs.size(); ++i)
        {
            float *data = (float *)outputs[i].data;
            for (int j = 0; j < outputs[i].rows; ++j, data += outputs[i].cols)
            {
                Mat scores = outputs[i].row(j).colRange(5, outputs[i].cols);
                Point classIdPoint;
                double confidence;
                // Get the value and location of the maximum score
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > confidence_)
                {
                    int centerX = static_cast<int>((data[0] * frame.cols));
                    int centerY = static_cast<int>((data[1] * frame.rows));
                    int width = static_cast<int>((data[2] * frame.cols));
                    int height = static_cast<int>((data[3] * frame.rows));
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    class_id.emplace_back(classIdPoint.x);
                    confidences.emplace_back((float)confidence);
                    boxes.emplace_back(Rect(left, top, width, height));
                }
            }
        }

        vector<int> indices;
        NMSBoxes(boxes, confidences, 0.5, 0.4, indices);
        for (size_t i = 0; i < indices.size(); ++i)
        {
            int idx = indices[i];
            Rect box = boxes[idx];
            DrawBoxes(class_id[idx], confidences[idx], box.x, box.y,
                      box.x + box.width, box.y + box.height, frame);
        }
    }


    void OpenCV::setTopConfidence(double confidence)
    {
        top_confidence_ = confidence;
    }
    double OpenCV::GetTopConfidence()
    {
        return top_confidence_;
    }
    int OpenCV::GetHotDogCount()
    {
        return hot_dog_count_;
    }

    // Draw the predicted bounding box
    void OpenCV::DrawBoxes(int classId, float confidence, int left, int top, int right, int bottom, Mat &frame)
    {
        if (!classes.empty() && classId == 52){
            hot_dog_count_++;
            if (confidence > top_confidence_)
            {
                setTopConfidence(confidence);
            }
            rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

            //Get the label for the class name and its confidence
            string label = format("%.2f", confidence);
            label = classes[classId] + ":" + label;

            //Display the label at the top of the bounding box
            int baseLine;
            Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            top = max(top, labelSize.height);
            rectangle(frame, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
            putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
        }
    }

    // Get the names of the output layers
    vector<String> GetOutputLayerNames(const Net &net)
    {
        vector<String> names;
            vector<int> outLayers = net.getUnconnectedOutLayers();
            vector<String> layersNames = net.getLayerNames();

            names.resize(outLayers.size());
            for (size_t i = 0; i < outLayers.size(); ++i)
                names[i] = layersNames[outLayers[i] - 1];
        return names;
    }
