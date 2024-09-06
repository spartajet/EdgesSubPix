#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include "EdgesSubPix.h"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    // ocl::setUseOpenCL(false);
    // const String keys =
    //                     "{help h usage ? |          | print this message            }"
    //                     "{@image         |          | image for edge detection      }"
    //                     "{@output        |edge.tiff | image for draw contours       }"
    //                     "{data           |          | edges data in txt format      }"
    //                     "{low            |20        | low threshold                 }"
    //                     "{high           |40        | high threshold                }"
    //                     "{mode           |1         | same as cv::findContours      }"
    //                     "{alpha          |1.0       | gaussian alpha              }";
    // CommandLineParser parser(argc, argv, keys);
    // parser.about("subpixel edge detection");
    //
    // if (!parser.check())
    // {
    //     parser.printErrors();
    //     return 0;
    // }
    //
    // if (parser.has("help"))
    // {
    //     parser.printMessage();
    //     return 0;
    // }
    //
    // if (!parser.has("@image"))
    // {
    //     parser.printMessage();
    //     return 0;
    // }
    //
    // String imageFile = parser.get<String>(0);
    // String outputFile = parser.get<String>("@output");
    // int low = parser.get<int>("low");
    // int high = parser.get<int>("high");
    // double alpha = parser.get<double>("alpha");
    // int mode = parser.get<int>("mode");

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


    return 0;
}
