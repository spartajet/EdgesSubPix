#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include "EdgesSubPix.h"
using namespace cv;
using namespace std;

void test1();
void test2();

int main(int argc, char *argv[])
{
    test2();
    return 0;
}

void test2()
{
    string imageFile = "B166300101CN1429-1.Bmp";
    int low=20;
    int high=40;
    double alpha=1.0;
    string outputFile = "edge.tiff";
    string data="edges.txt";

    Mat image = imread(imageFile, IMREAD_GRAYSCALE);
    // vector<Contour> contours;
    vector<Vec4i> hierarchy;
    int64 t0 = getCPUTickCount();
    uchar* image_data = image.data;
    int width=image.cols;
    int height=image.rows;
    PointResult result=EdgesSubPixPoints(image_data, width, height, alpha, low, high, 500, 1000);

    int64 t1 = getCPUTickCount();
    cout << "execution time is " << (t1 - t0) / (double)getTickFrequency() << " seconds" << endl;
    cout<<"length of result is "<<result.length<<endl;
    // if (parser.has("data"))

}

void test1()
{
    string imageFile = "B166300101CN1429-1.Bmp";
    int low=20;
    int high=40;
    double alpha=1.0;
    string outputFile = "edge.tiff";
    string data="edges.txt";

    Mat image = imread(imageFile, IMREAD_GRAYSCALE);
    // vector<Contour> contours;
    vector<Vec4i> hierarchy;
    int64 t0 = getCPUTickCount();
    vector<Contour> contours= EdgesSubPix(image, alpha, low, high);
    int64 t1 = getCPUTickCount();
    cout << "execution time is " << (t1 - t0) / (double)getTickFrequency() << " seconds" << endl;

    // if (parser.has("data"))
    // {
    FileStorage fs(data, FileStorage::WRITE | FileStorage::FORMAT_YAML);
    fs << "contours" << "[";
    for (size_t i = 0; i < contours.size(); ++i)
    {
        printf("length of contour %d is %d\n", i, contours[i].points.size());
        fs << "{:";
        fs << "points" << contours[i].points;
        fs << "response" << contours[i].response;
        fs << "direction" << contours[i].direction;
        fs << "}";
    }
    fs << "]";
    fs.release();
    // }


    cv::Mat colorImage;
    cv::cvtColor(image, colorImage, COLOR_GRAY2BGR);
    vector<vector<Point>> ocvContours;
    for (size_t i = 0; i < contours.size(); ++i) {
        cv::Mat pts(contours[i].points);
        vector<Point> c;
        pts.convertTo(c, CV_32S);
        ocvContours.push_back(std::move(c));
    }

    cv::drawContours(colorImage, ocvContours, -1, cv::Scalar(0, 255, 0));
    cv::imwrite(outputFile, colorImage);

}
